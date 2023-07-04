#include "peripherals/local_timer_regs.h"
#include "peripherals/timer_regs.h"
#include "peripherals/irq.h"
void enable_int_aux()
{
    REGS_IRQ->ENABLE_IRQS_1 |= 1<<29;
}
void enable_loc_timer_irq()
{
    REGS_LOC_TIMER->local_timer_base |= ((1<<28) | (1<<29));
}
void enable_timer_1()
{
	REGS_IRQ->ENABLE_IRQS_1 |= SYSTEM_TIMER_IRQ_1;
}
void enable_timer_3()
{
	REGS_IRQ->ENABLE_IRQS_1 |= SYSTEM_TIMER_IRQ_3;
}

void enable_interrupt_controller()
{
    enable_int_aux();
    enable_timer_1();
    // enable_timer_3();
    // enable_loc_timer_irq();
}