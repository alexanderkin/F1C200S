#ifndef SYS_DRAM_H
#define SYS_DRAM_H

typedef enum {
    DRAM_SCONR = 0x000,
    DRAM_STMG0R = 0x004,
    DRAM_STMG1R = 0x008,
    DRAM_SCTLR = 0x00C,
    DRAM_SREFR = 0x010,
    DRAM_SEXTMR = 0x014,
    DRAM_DDLYR = 0x024,
    DRAM_DADRR = 0x028,
    DRAM_DVALR = 0x02C,
    DRAM_DRPTR0 = 0x030,
    DRAM_DRPTR1 = 0x034,
    DRAM_DRPTR2 = 0x038,
    DRAM_DRPTR3 = 0x03C,
    DRAM_SEFR = 0x040,
    DRAM_MAE = 0x044,
    DRAM_ASPR = 0x048,
    DRAM_SDLY0 = 0x04C,
    DRAM_SDLY1 = 0x050,
    DRAM_SDLY2 = 0x054,
    DRAM_MCR0 = 0x100,
    DRAM_MCR1 = 0x104,
    DRAM_MCR2 = 0x108,
    DRAM_MCR3 = 0x10C,
    DRAM_MCR4 = 0x110,
    DRAM_MCR5 = 0x114,
    DRAM_MCR6 = 0x118,
    DRAM_MCR7 = 0x11C,
    DRAM_MCR8 = 0x120,
    DRAM_MCR9 = 0x124,
    DRAM_MCR10 = 0x128,
    DRAM_MCR11 = 0x12C,
    DRAM_BWCR = 0x140,
} dram_regs_e;

uint8_t sys_dram_init(void);

#endif // SYS_DRAM_H