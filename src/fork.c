#include "constants/memory.h"
#include "structures/sched.h"
#include "funcs/fork.h"
#include "structures/common.h"
#include "funcs/printf.h"

int copy_process (u64 fn, u64 arg)
{
    printf("copy process\n\r");
	preempt_disable();
	struct task_struct *p;

	p = (struct task_struct *) get_free_page();
	if (p==0)
	{
		return 1;
	}
	p->priority = current->priority;
	p->state = TASK_RUNNING;
	p->counter = p->priority;
	p->preempt_count = 1; //disable preemtion until schedule_tail

	p->cpu_context.x19 = fn;
	p->cpu_context.x20 = arg;
	p->cpu_context.pc = (u64)ret_from_fork;
	p->cpu_context.sp = (u64)p + PAGE_SIZE;
	int pid = nr_tasks++;
    p->pid=nr_tasks;
    printf("PID[%d]\n\r",pid);
    printf("nr_tasks[%d]\n\r",nr_tasks);
	task[pid] = p;
	preempt_enable();
    printf("ENDcopyEND\n\r");
	return 0;
}
