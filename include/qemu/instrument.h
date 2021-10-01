#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#ifdef CONFIG_PLUGINS_SWAT

bool plugins_need_before_insn(target_ulong pc, CPUState *cpu);
void plugins_instrument_before_insn(target_ulong pc, CPUState *cpu);
void plugins_instrument_tb_start(target_ulong pc, CPUState *cpu);

#else /* CONFIG_PLUGINS_SWAT */

inline bool plugins_need_before_insn(target_ulong pc, CPUState *cpu)
{
    return false;
}
inline void plugins_instrument_before_insn(target_ulong pc, CPUState *cpu) {}
inline void plugins_instrument_tb_start(target_ulong pc, CPUState *cpu) {}

#endif /* CONFIG_PLUGINS_SWAT */

#endif /* INSTRUMENT_H */
