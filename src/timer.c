#include "utils.h"
#include "printf.h"
#include "common.h"
#include "sched.h"
#include "peripherals/timer_regs.h"


const u32 interval_1 = CLOCKHZ/10;

const u32 interval_3 = CLOCKHZ;

void timer_init()
{
	REGS_TIMER->TIMER_C[1] = REGS_TIMER->TIMER_CLO + interval_1;
	REGS_TIMER->TIMER_C[3] = REGS_TIMER->TIMER_CLO + interval_3;
}
void handle_timer_1_irq()
{
	//printf("[T]");
	REGS_TIMER->TIMER_C[1]+=interval_1;
	REGS_TIMER->TIMER_CS |= TIMER_CS_M1;
	timer_tick();
}
void handle_timer_3_irq()
{
	REGS_TIMER->TIMER_C[3]+=interval_3;
	REGS_TIMER->TIMER_CS |= TIMER_CS_M3;
}

u64 timer_get_ticks()
{
	u32 hi = REGS_TIMER->TIMER_CHI;
	u32 lo = REGS_TIMER->TIMER_CLO;
	if (hi !=REGS_TIMER->TIMER_CHI)
	{
		hi = REGS_TIMER->TIMER_CHI;
		lo = REGS_TIMER->TIMER_CLO;
	}
	return ((u64)hi << 32) | lo;
}

//milliseconds
void timer_sleep(u32 ms)
{
	//printf("SLEEP\n\r");
	u64 start = timer_get_ticks();
	while (timer_get_ticks() < start + (ms * 1000)){

	}
	
}
// static unsigned int interval = 999999;
// unsigned int curVal = 0;

// void timer_init ( unsigned int interval_in )
// {
// 	interval = interval_in;
// 	curVal = read32(REGS_TIMER->TIMER_CLO);
// 	curVal += interval;
// 	write32(REGS_TIMER->TIMER_C1, curVal);
// }

// void handle_timer_irq( void ) 
// {
// 	curVal += interval;
// 	write32(REGS_TIMER->TIMER_C1, curVal);
// 	write32(REGS_TIMER->TIMER_CS, TIMER_CS_M1);
// 	printf("Timer interrupt received\n\r");
// }