#pragma once
#include "peripherals/base.h"
#include "common.h"

#define SYSTEM_TIMER_IRQ_0	(1 << 0)
#define SYSTEM_TIMER_IRQ_1	(1 << 1)
#define SYSTEM_TIMER_IRQ_2	(1 << 2)
#define SYSTEM_TIMER_IRQ_3	(1 << 3)
#define AUX_IRQ (1<<29)

struct irq_regs
{
    reg32 IRQ_BASIC_PENDING;
    reg32 IRQ_PENDING_1	;
    reg32 IRQ_PENDING_2	;
    reg32 FIQ_CONTROL;
    reg32 ENABLE_IRQS_1;
    reg32 ENABLE_IRQS_2;
    reg32 ENABLE_BASIC_IRQS;
    reg32 DISABLE_IRQS_1;
    reg32 DISABLE_IRQS_2;
    reg32 DISABLE_BASIC_IRQS;
};

#define REGS_IRQ ((struct irq_regs *)(PBASE + 0xB000 + 0x200))

