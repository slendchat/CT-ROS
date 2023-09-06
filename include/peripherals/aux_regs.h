#pragma once
#include "common.h"
#include "peripherals/base.h"

struct aux_regs
{
    reg32 irq;
    reg32 enables;
    reg32 reserved[14];
    reg32 MU_IO_REG;
    reg32 MU_IER_REG;
    reg32 MU_IIR_REG;
    reg32 MU_LCR_REG;
    reg32 MU_MCR_REG;
    reg32 MU_LSR_REG;
    reg32 MU_MSR_REG;
    reg32 MU_SCRATCH;
    reg32 MU_CNTL_REG;
    reg32 MU_STAT_REG;
    reg32 MU_BAUD_REG;
};

#define REGS_AUX ((struct aux_regs*)(PBASE+0x00215000))