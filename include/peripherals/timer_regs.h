#pragma once
#include "peripherals/base.h"
#include "common.h"

struct timer_regs
{
    reg32 TIMER_CS;
    reg32 TIMER_CLO;
    reg32 TIMER_CHI;
    reg32 TIMER_C[4];
};

#define REGS_TIMER ((struct timer_regs *)(PBASE + 0x00003000))

#define CLOCKHZ 999999

// #define TIMER_CS_M0	(1 << 0)
#define TIMER_CS_M1	(1 << 1)
// #define TIMER_CS_M2	(1 << 2)
#define TIMER_CS_M3	(1 << 3)