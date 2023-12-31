#include "sched.h"
#include "irq.h"
#include "printf.h"
#include "utils.h"
#include "mm.h"
#include "common.h"

static struct task_struct init_task = INIT_TASK;
struct task_struct *current = &(init_task);
struct task_struct * task[NR_TASKS] = {&(init_task), };
int nr_tasks = 1;

void sched_init()
{
	for (int i = 1; i < NR_TASKS; i++)
	{
		task[i] = NULL;
	}
	
}

void preempt_disable(void)
{
	current->preempt_count++;
}

void preempt_enable(void)
{
	current->preempt_count--;
}


void _schedule(void)
{
	preempt_disable();
	int next,c;
	struct task_struct * p;
	while (1) {
		c = -1;
		next = 0;
		for (int i = 0; i < NR_TASKS; i++){
			p = task[i];
			if (p && p->state == TASK_RUNNING && p->counter > c) {
				c = p->counter;
				next = i;
			}
			
		}
		if (c) {
			break;
		}
		for (int i = 0; i < NR_TASKS; i++) {
			p = task[i];
			if (p) {
				p->counter = (p->counter >> 1) + p->priority;
			}
		}
	}
	printf("\r\nid[%d]\r\n",task[next]->pid);
	switch_to(task[next]);
	preempt_enable();
}

void switch_to(struct task_struct * next) 
{
	if (current == next) 
		return;

	struct task_struct * prev = current;
	current = next;
	set_pgd(next->mm.pgd);

	if (current->signal.TIF_SIGPENDING==228)
	{
		printf("[CATCH_SIG]");
		SIGNALS sig = current->signal.signal;
		current->signal.TIF_SIGPENDING=0;
		current->signal.signal=SIGNO;
		do_signal(sig);
	}
	else
	{
		cpu_switch_to(prev, next);
	}
	
}

void schedule(void)
{
	current->counter = 0;
	_schedule();
}

void schedule_tail(void) {
	preempt_enable();
}


void timer_tick()
{
	--current->counter;
	if (current->counter>0 || current->preempt_count >0) {
		return;
	}
	current->counter=0;
	enable_irq();
	_schedule();
	disable_irq();
}
void reprior(u32 prior, u32 id)
{
	preempt_disable();
	for (int i = 0; i < NR_TASKS; i++)
	{
		if (id == task[i]->pid)
		{
			if (prior > 0 && prior <= 40 && task[i]!=NULL)
			{
				printf("\n\rreprior[id%d][pr%d]\n\r",id,prior);
				task[i]->priority = prior;
			}
			break;
		}
		
	}
	preempt_enable();
}
void exit_process(){
	preempt_disable();
	for (int i = 0; i < NR_TASKS; i++){
		if (task[i] == current) {
			task[i]->state = TASK_ZOMBIE;
			break;
		}
	}
	preempt_enable();
	schedule();
}
int get_id()
{
	return current->pid;
}
void do_signal(SIGNALS sig)
{
	switch (sig)
	{
	case SIGTERM:
		current->state=TASK_ZOMBIE;
		_schedule();
		break;
	case SIGSTOP:
		current->state=TASK_HALT;
		_schedule();
		break;
	case SIGKILL:
		current->state=TASK_ZOMBIE;
		_schedule();
		break;
	
	default:
		break;
	}
}

