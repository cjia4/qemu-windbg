#include "qemu/osdep.h"
#include "qemu-common.h"
#include "cpu.h"
#include "qemu/error-report.h"
#include "qemu/plugins.h"
#include "qemu/instrument.h"
#include "tcg/tcg.h"
#include "tcg/tcg-op.h"
#include "qemu/queue.h"
#include "qemu/option.h"
#include "monitor/monitor.h"
#include "qapi/qmp/qdict.h"
#include "exec/exec-all.h"
#include <gmodule.h>

typedef bool (*PluginInitFunc)(const char *);
typedef bool (*PluginNeedsBeforeInsnFunc)(uint64_t, void *);
typedef void (*PluginBeforeInsnFunc)(uint64_t, void *);
typedef bool (*PluginNeedsBeforeTBFunc)(uint64_t, void *);
typedef void (*PluginBeforeTBFunc)(uint64_t, void *);

typedef struct QemuPluginInfo {
    const char *filename;
    const char *args;
    GModule *g_module;

    PluginInitFunc init;
    PluginNeedsBeforeInsnFunc needs_before_insn;
    PluginBeforeInsnFunc before_insn;
    PluginNeedsBeforeTBFunc needs_before_tb;
    PluginBeforeTBFunc before_tb;

    QLIST_ENTRY(QemuPluginInfo) next;
} QemuPluginInfo;

static QLIST_HEAD(, QemuPluginInfo) qemu_plugins
                                = QLIST_HEAD_INITIALIZER(qemu_plugins);

static QemuOptsList qemu_plugin_swat_opts = {
    .name = "plugin-swat",
    .head = QTAILQ_HEAD_INITIALIZER(qemu_plugin_swat_opts.head),
    .desc = {
        {
            .name = "file",
            .type = QEMU_OPT_STRING,
        },{
            .name = "args",
            .type = QEMU_OPT_STRING,
        },
        { /* end of list */ }
    },
};

void qemu_plugin_parse_cmd_args(const char *optarg)
{
    QemuOpts *opts = qemu_opts_parse_noisily(&qemu_plugin_swat_opts, optarg, false);
    qemu_plugin_load(qemu_opt_get(opts, "file"),
        qemu_opt_get(opts, "args"));
}

static void qemu_plugin_unload(QemuPluginInfo *info)
{
    QLIST_REMOVE(info, next);
    g_module_close(info->g_module);
    g_free((gpointer)info->filename);
    g_free((gpointer)info->args);
    g_free(info);
}

QemuPluginInfo *qemu_plugin_load(const char *filename, const char *args)
{
    GModule *g_module;
    QemuPluginInfo *info = NULL;
    if (!filename) {
        error_report("plugin name was not specified");
        return NULL;
    }
    g_module = g_module_open(filename,
        G_MODULE_BIND_LAZY | G_MODULE_BIND_LOCAL);
    if (!g_module) {
        error_report("can't load plugin '%s'", filename);
        return NULL;
    }
    info = g_new0(QemuPluginInfo, 1);
    info->filename = g_strdup(filename);
    info->g_module = g_module;
    if (args) {
        info->args = g_strdup(args);
    }

    g_module_symbol(g_module, "plugin_init", (gpointer *)&info->init);

    /* Get the instrumentation callbacks */
    g_module_symbol(g_module, "plugin_needs_before_insn",
        (gpointer *)&info->needs_before_insn);
    g_module_symbol(g_module, "plugin_before_insn",
        (gpointer *)&info->before_insn);
    g_module_symbol(g_module, "plugin_needs_before_tb",
        (gpointer *)&info->needs_before_tb);
    g_module_symbol(g_module, "plugin_before_tb",
        (gpointer *)&info->before_tb);

    QLIST_INSERT_HEAD(&qemu_plugins, info, next);

    return info;
}

void monitor_load_plugin(Monitor *mon, const QDict *qdict)
{
    const char *file = qdict_get_try_str(qdict, "file");
    const char *args = qdict_get_try_str(qdict, "args");
    QemuPluginInfo *plugin = qemu_plugin_load(file, args);
    if (plugin) {
        if (plugin->init) {
            if (!plugin->init(plugin->args)) {
                monitor_printf(mon, "Can't initialize the plugin\n");
                qemu_plugin_unload(plugin);
                return;
            }
        }
    } else {
        monitor_printf(mon, "Can't load the plugin\n");
        return;
    }
    tb_flush(first_cpu);
}

bool plugins_need_before_insn(target_ulong pc, CPUState *cpu)
{
    QemuPluginInfo *info;
    QLIST_FOREACH(info, &qemu_plugins, next) {
        if (info->needs_before_insn && info->needs_before_insn(pc, cpu)) {
            return true;
        }
    }

    return false;
}

void plugins_instrument_before_insn(target_ulong pc, CPUState *cpu)
{
    TCGv t_pc = tcg_const_tl(pc);
    TCGv_ptr t_cpu = tcg_const_ptr(cpu);
    /* We will dispatch plugins' callbacks in our own helper below */
    gen_helper_before_insn(t_pc, t_cpu);
    tcg_temp_free(t_pc);
    tcg_temp_free_ptr(t_cpu);
}

void plugins_instrument_tb_start(target_ulong pc, CPUState *cpu)
{
    bool needs = false;
    QemuPluginInfo *info;
    QLIST_FOREACH(info, &qemu_plugins, next) {
        if (info->needs_before_tb && info->needs_before_tb(pc, cpu)) {
            needs = true;
            break;
        }
    }
    if (needs) {
        TCGv t_pc = tcg_const_tl(pc);
        TCGv_ptr t_cpu = tcg_const_ptr(cpu);
        /* We will dispatch plugins' callbacks in our own helper below */
        gen_helper_before_tb(t_pc, t_cpu);
        tcg_temp_free(t_pc);
        tcg_temp_free_ptr(t_cpu);
    }
}

void helper_before_tb(target_ulong pc, void *cpu)
{
    QemuPluginInfo *info;
    QLIST_FOREACH(info, &qemu_plugins, next) {
        if (info->needs_before_tb && info->needs_before_tb(pc, cpu)) {
            if (info->before_tb) {
                info->before_tb(pc, cpu);
            }
        }
    }
}

void helper_before_insn(target_ulong pc, void *cpu)
{
    QemuPluginInfo *info;
    QLIST_FOREACH(info, &qemu_plugins, next) {
        if (info->needs_before_insn && info->needs_before_insn(pc, cpu)) {
            if (info->before_insn) {
                info->before_insn(pc, cpu);
            }
        }
    }
}

void qemu_plugins_init(void)
{
    QemuPluginInfo *info;
    QemuPluginInfo *next;
    QLIST_FOREACH_SAFE(info, &qemu_plugins, next, next) {
        if (info->init) {
            if (!info->init(info->args)) {
                error_report("can't init plugin '%s'", info->filename);
                qemu_plugin_unload(info);
            }
        }
    }
}
