#ifndef REGNUM_H
#define REGNUM_H

/* Register numbers */
/* Taken from GDB, because we are using GDB interface for
 * retrieving the register values from plugins. */

enum i386_regnum
{
  I386_EAX_REGNUM,
  I386_ECX_REGNUM,
  I386_EDX_REGNUM,
  I386_EBX_REGNUM,
  I386_ESP_REGNUM,
  I386_EBP_REGNUM,
  I386_ESI_REGNUM,
  I386_EDI_REGNUM,
  I386_EIP_REGNUM,
  I386_EFLAGS_REGNUM,
  I386_CS_REGNUM,
  I386_SS_REGNUM,
  I386_DS_REGNUM,
  I386_ES_REGNUM,
  I386_FS_REGNUM,
  I386_GS_REGNUM,
  I386_FS_BASE_REGNUM,
  I386_GS_BASE_REGNUM,
  I386_KERNEL_GS_BASE_REGNUM,
  I386_CR0_REGNUM,
  I386_CR2_REGNUM,
  I386_CR3_REGNUM,
  I386_CR4_REGNUM,
  I386_CR8_REGNUM,
  I386_EFER_REGNUM,
  I386_ST0_REGNUM,
  I386_MXCSR_REGNUM = 40,
  I386_YMM0H_REGNUM,
  I386_YMM7H_REGNUM = I386_YMM0H_REGNUM + 7,
  I386_BND0R_REGNUM,
  I386_BND3R_REGNUM = I386_BND0R_REGNUM + 3,
  I386_BNDCFGU_REGNUM,
  I386_BNDSTATUS_REGNUM,
  I386_K0_REGNUM,
  I386_K7_REGNUM = I386_K0_REGNUM + 7,
  I386_ZMM0H_REGNUM,
  I386_ZMM7H_REGNUM = I386_ZMM0H_REGNUM + 7,
  I386_PKRU_REGNUM,
  /* Non-gdb registers */
  I386_CS_BASE_REGNUM,
  I386_SS_BASE_REGNUM,
  I386_TR_BASE_REGNUM,
};

enum amd64_regnum
{
  AMD64_RAX_REGNUM,   /* %rax */
  AMD64_RBX_REGNUM,   /* %rbx */
  AMD64_RCX_REGNUM,   /* %rcx */
  AMD64_RDX_REGNUM,   /* %rdx */
  AMD64_RSI_REGNUM,   /* %rsi */
  AMD64_RDI_REGNUM,   /* %rdi */
  AMD64_RBP_REGNUM,   /* %rbp */
  AMD64_RSP_REGNUM,   /* %rsp */
  AMD64_R8_REGNUM,    /* %r8 */
  AMD64_R9_REGNUM,    /* %r9 */
  AMD64_R10_REGNUM,   /* %r10 */
  AMD64_R11_REGNUM,   /* %r11 */
  AMD64_R12_REGNUM,   /* %r12 */
  AMD64_R13_REGNUM,   /* %r13 */
  AMD64_R14_REGNUM,   /* %r14 */
  AMD64_R15_REGNUM,   /* %r15 */
  AMD64_RIP_REGNUM,   /* %rip */
  AMD64_EFLAGS_REGNUM,    /* %eflags */
  AMD64_CS_REGNUM,    /* %cs */
  AMD64_SS_REGNUM,    /* %ss */
  AMD64_DS_REGNUM,    /* %ds */
  AMD64_ES_REGNUM,    /* %es */
  AMD64_FS_REGNUM,    /* %fs */
  AMD64_GS_REGNUM,    /* %gs */
  AMD64_ST0_REGNUM = 24,  /* %st0 */
  AMD64_ST1_REGNUM,   /* %st1 */
  /* TODO: Taken from QEMU, not from GDB */
  AMD64_CTL_REGNUM = 27,
  AMD64_CR3_REGNUM = AMD64_CTL_REGNUM + 2,
  AMD64_FCTRL_REGNUM = AMD64_ST0_REGNUM + 8,
  AMD64_FSTAT_REGNUM = AMD64_ST0_REGNUM + 9,
  AMD64_FTAG_REGNUM = AMD64_ST0_REGNUM + 10,
  AMD64_XMM0_REGNUM = 40, /* %xmm0 */
  AMD64_XMM1_REGNUM,    /* %xmm1 */
  AMD64_MXCSR_REGNUM = AMD64_XMM0_REGNUM + 16,
  AMD64_YMM0H_REGNUM,   /* %ymm0h */
  AMD64_YMM15H_REGNUM = AMD64_YMM0H_REGNUM + 15,
  AMD64_BND0R_REGNUM = AMD64_YMM15H_REGNUM + 1,
  AMD64_BND3R_REGNUM = AMD64_BND0R_REGNUM + 3,
  AMD64_BNDCFGU_REGNUM,
  AMD64_BNDSTATUS_REGNUM,
  AMD64_XMM16_REGNUM,
  AMD64_XMM31_REGNUM = AMD64_XMM16_REGNUM + 15,
  AMD64_YMM16H_REGNUM,
  AMD64_YMM31H_REGNUM = AMD64_YMM16H_REGNUM + 15,
  AMD64_K0_REGNUM,
  AMD64_K7_REGNUM = AMD64_K0_REGNUM + 7,
  AMD64_ZMM0H_REGNUM,
  AMD64_ZMM31H_REGNUM = AMD64_ZMM0H_REGNUM + 31,
  AMD64_PKRU_REGNUM,
  AMD64_FSBASE_REGNUM,
  AMD64_GSBASE_REGNUM,
  /* Non-gdb registers */
  AMD64_TR_BASE_REGNUM,
};

enum arm_regnum {
  ARM_A1_REGNUM = 0,		/* first integer-like argument */
  ARM_A4_REGNUM = 3,		/* last integer-like argument */
  ARM_AP_REGNUM = 11,
  ARM_IP_REGNUM = 12,
  ARM_SP_REGNUM = 13,		/* Contains address of top of stack */
  ARM_LR_REGNUM = 14,		/* address to return to from a function call */
  ARM_PC_REGNUM = 15,		/* Contains program counter */
  ARM_F0_REGNUM = 16,		/* first floating point register */
  ARM_F3_REGNUM = 19,		/* last floating point argument register */
  ARM_F7_REGNUM = 23, 		/* last floating point register */
  ARM_FPS_REGNUM = 24,		/* floating point status register */
  ARM_PS_REGNUM = 25,		/* Contains processor status */
  ARM_WR0_REGNUM,		/* WMMX data registers.  */
  ARM_WR15_REGNUM = ARM_WR0_REGNUM + 15,
  ARM_WC0_REGNUM,		/* WMMX control registers.  */
  ARM_WCSSF_REGNUM = ARM_WC0_REGNUM + 2,
  ARM_WCASF_REGNUM = ARM_WC0_REGNUM + 3,
  ARM_WC7_REGNUM = ARM_WC0_REGNUM + 7,
  ARM_WCGR0_REGNUM,		/* WMMX general purpose registers.  */
  ARM_WCGR3_REGNUM = ARM_WCGR0_REGNUM + 3,
  ARM_WCGR7_REGNUM = ARM_WCGR0_REGNUM + 7,
  ARM_D0_REGNUM,		/* VFP double-precision registers.  */
  ARM_D31_REGNUM = ARM_D0_REGNUM + 31,
  ARM_FPSCR_REGNUM,

  /* Non-gdb registers */
  ARM_SP_USR_REGNUM,
  ARM_TTBR0_EL1,
  ARM_TTBR1_EL1,

  ARM_NUM_REGS,

  /* Other useful registers.  */
  ARM_FP_REGNUM = 11,		/* Frame register in ARM code, if used.  */
  THUMB_FP_REGNUM = 7,		/* Frame register in Thumb code, if used.  */
  ARM_NUM_ARG_REGS = 4, 
  ARM_LAST_ARG_REGNUM = ARM_A4_REGNUM,
  ARM_NUM_FP_ARG_REGS = 4,
  ARM_LAST_FP_ARG_REGNUM = ARM_F3_REGNUM
};

enum aarch64_regnum
{
  AARCH64_X0_REGNUM,		/* First integer register.  */
  AARCH64_FP_REGNUM = AARCH64_X0_REGNUM + 29,	/* Frame register, if used.  */
  AARCH64_LR_REGNUM = AARCH64_X0_REGNUM + 30,	/* Return address.  */
  AARCH64_SP_REGNUM,		/* Stack pointer.  */
  AARCH64_PC_REGNUM,		/* Program counter.  */
  AARCH64_CPSR_REGNUM,		/* Current Program Status Register.  */
  AARCH64_V0_REGNUM,		/* First fp/vec register.  */
  AARCH64_V31_REGNUM = AARCH64_V0_REGNUM + 31,	/* Last fp/vec register.  */
  AARCH64_SVE_Z0_REGNUM = AARCH64_V0_REGNUM,	/* First SVE Z register.  */
  AARCH64_SVE_Z31_REGNUM = AARCH64_V31_REGNUM,  /* Last SVE Z register.  */
  AARCH64_FPSR_REGNUM,		/* Floating Point Status Register.  */
  AARCH64_FPCR_REGNUM,		/* Floating Point Control Register.  */
  AARCH64_SVE_P0_REGNUM,	/* First SVE predicate register.  */
  AARCH64_SVE_P15_REGNUM = AARCH64_SVE_P0_REGNUM + 15,	/* Last SVE predicate
							   register.  */
  AARCH64_SVE_FFR_REGNUM,	/* SVE First Fault Register.  */
  AARCH64_SVE_VG_REGNUM,	/* SVE Vector Granule.  */

  /* Non-gdb registers */
  AARCH64_SP_EL0,
  AARCH64_SP_EL1,
  AARCH64_SP_EL2,
  AARCH64_SP_EL3,
  AARCH64_TTBR0_EL1,
  AARCH64_TTBR1_EL1,

  /* Other useful registers.  */
  AARCH64_LAST_X_ARG_REGNUM = AARCH64_X0_REGNUM + 7,
  AARCH64_STRUCT_RETURN_REGNUM = AARCH64_X0_REGNUM + 8,
  AARCH64_LAST_V_ARG_REGNUM = AARCH64_V0_REGNUM + 7
};

#endif
