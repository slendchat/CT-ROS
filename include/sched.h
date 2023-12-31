#ifndef _SCHED_H
#define _SCHED_H

#define THREAD_CPU_CONTEXT			0 		// offset of cpu_context in task_struct 

#ifndef __ASSEMBLER__
#include "common.h"

#define THREAD_SIZE				4096

#define NR_TASKS				64 

#define FIRST_TASK task[0]
#define LAST_TASK task[NR_TASKS-1]

#define TASK_RUNNING		0
#define TASK_ZOMBIE			1
#define TASK_HALT			2
#define TASK_DEL			3

#define PF_KTHREAD				0x00000002	

typedef enum _SIGNALS {
	SIGNO = 0,
	SIGTERM,
	SIGSTOP,
	SIGKILL
}SIGNALS;


extern struct task_struct *current;
extern struct task_struct * task[NR_TASKS];
extern int nr_tasks;

struct cpu_context {
	unsigned long x19;
	unsigned long x20;
	unsigned long x21;
	unsigned long x22;
	unsigned long x23;
	unsigned long x24;
	unsigned long x25;
	unsigned long x26;
	unsigned long x27;
	unsigned long x28;
	unsigned long fp;
	unsigned long sp;
	unsigned long pc;
};

#define MAX_PROCESS_PAGES			16	

struct user_page {
	unsigned long phys_addr;
	unsigned long virt_addr;
};

struct mm_struct {
	unsigned long pgd;
	int user_pages_count;
	struct user_page user_pages[MAX_PROCESS_PAGES];
	int kernel_pages_count;
	unsigned long kernel_pages[MAX_PROCESS_PAGES];
};

struct SIG_struct
{
	SIGNALS signal;
	volatile u32 TIF_SIGPENDING;
};


struct task_struct {
	struct cpu_context cpu_context;
	long state;	
	long counter;
	long priority;
	long preempt_count;
	unsigned long flags;
	long pid;
	struct mm_struct mm;
	struct SIG_struct signal;
};

extern void sched_init(void);
extern void schedule(void);
extern void timer_tick(void);
extern void preempt_disable(void);
extern void preempt_enable(void);
extern void switch_to(struct task_struct* next);
extern void cpu_switch_to(struct task_struct* prev, struct task_struct* next);
extern void exit_process(void);
extern void reprior(u32 prior, u32 id);
extern int get_id();
extern void sched_init();
void do_signal(SIGNALS sig);
#define INIT_TASK \
/*cpu_context*/ { { 0,0,0,0,0,0,0,0,0,0,0,0,0}, \
/* state etc */	 TASK_RUNNING,0,5,0,PF_KTHREAD,1, \
/* mm */ { 0, 0, {{0}}, 0, {0}}, \
/* SIG */ {0,0} \
}
#endif
#endif
