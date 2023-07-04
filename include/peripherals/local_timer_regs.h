#pragma once
#include "peripherals/base.h"
#include "structures/common.h"
//local_timer
struct loc_timer_regs
{
    reg32 local_interrupt_routing;
    reg32 reserved[3];
    reg32 local_timer_base;
    reg32 loc_timer_IRQ_clear_reload;
    reg32 reserved2[9];
    reg32 core[4];
};

#define REGS_LOC_TIMER ((struct loc_timer_regs *)(0x40000024))

#define pending_local_timer (1<<11)