#pragma once
#include "structures/common.h"
void timer_init ();
void handle_timer_1_irq();
void handle_timer_3_irq();
u64 timer_get_ticks();
void timer_sleep(u32 ms);