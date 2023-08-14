#ifndef	_TIMER_H
#define	_TIMER_H
#include "common.h"
void timer_init ( void );
void handle_timer_1_irq( void );
u64 timer_get_ticks();
void timer_sleep(u32 ms);
#endif  /*_TIMER_H */
