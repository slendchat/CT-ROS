#pragma once
#define THREAD_CPU_CONTEXT 0

#ifndef __ASSEMBLER__

#include "structures/proc.h"

#define NR_TASKS 64
#define HZ 100

extern struct task_struct *current;
extern struct task_struct *task[NR_TASKS];
extern int nr_tasks;

#define FIRST_TASK task[0]
#define LAST_TASK task[NR_TASKS-1]

#define TASK_RUNNING		    0
#define TASK_INTERRUPTIBLE	    1
#define TASK_UNINTERRUPTIBLE	2
#define TASK_ZOMBIE		        3
#define TASK_STOPPED		    4

void task_init();
void schedule();
void timer_tick();
void preempt_disable();
void preempt_enable();
extern void switch_to(struct task_struct* next);
extern void cpu_switch_to(struct task_struct* prev, struct task_struct* next);
#endif