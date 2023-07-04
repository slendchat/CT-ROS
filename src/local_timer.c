#include "funcs/printf.h"
#include "peripherals/local_timer_regs.h"
#include "funcs/utils.h"

void loc_timer_init(unsigned int interval)
{
    REGS_LOC_TIMER->local_timer_base |= (interval & 0b1111111111111111111111111111);
}

void handle_loc_timer_irq()
{
    // printf("[LOCAL TIMER]");
    REGS_LOC_TIMER->loc_timer_IRQ_clear_reload = 1 << 31;
}

