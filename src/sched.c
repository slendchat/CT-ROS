#include "structures/common.h"
#include "structures/sched.h"
#include "structures/proc.h"
#include "funcs/int.h"
#include "funcs/printf.h"


static struct task_struct init_task;
struct task_struct *task[NR_TASKS];
struct task_struct *current = &(init_task);

int nr_tasks=1;
void task_init()
{
	printf("task_init\n\r");
	for (int i = 0; i < NR_TASKS; i++)
	{
		task[i]=NULL;
	}
	init_task.cpu_context.pc=0;
	init_task.cpu_context.fp=0;
	init_task.cpu_context.sp=0;
	init_task.cpu_context.x19=0;
	init_task.cpu_context.x20=0;
	init_task.cpu_context.x21=0;
	init_task.cpu_context.x22=0;
	init_task.cpu_context.x23=0;
	init_task.cpu_context.x24=0;
	init_task.cpu_context.x25=0;
	init_task.cpu_context.x26=0;
	init_task.cpu_context.x27=0;
	init_task.cpu_context.x28=0;
	init_task.counter=2;
	init_task.pid=nr_tasks;
	init_task.priority=1;
	task[0]=&init_task;
}
void preempt_disable()
{
	current->preempt_count++;
}

void preempt_enable()
{
	current->preempt_count--;
}

void _schedule()
{
	printf("__schedule\n\r");
	preempt_disable();
	struct task_struct *p;
	int next,c;
	while (1)
	{
		c = -1;
		next = 0;
		for (int i = 0; i < NR_TASKS; i++)
		{
			if (task[i]!=NULL)
			{
				p = task[i];
				if (((int)(p->counter) > c) && (p->state==TASK_RUNNING))
				{
					c = (int)(p->counter);
					next = i;
					printf("next= %d",next);
				}				
			}
			
		}
		if (c==0)
		{
			printf("c=0\n\r");
			for (int i = 0; i < NR_TASKS; i++)
			{
				if (task[i]!=NULL)
				{
					p = task[i];
					p->counter=(p->counter>>1)+p->priority;
				}			
			}
		}
		else
		{
			break;
		}
	}
	printf("next = %d\n\r",next);
	switch_to(task[next]);
	preempt_enable();
}
void switch_to(struct task_struct* next)
{
	printf("switch_to\n\r");
	if (current != next)
	{
		struct task_struct *prev = current;
		current = next;
		cpu_switch_to(prev,next);
	}
	
}
void schedule()
{
	printf("schedule\n\r");
	current->counter=0;
	_schedule();
}
void schedule_tail(void)
{
	printf("tail\n\r");
	preempt_enable();
}
void timer_tick()
{
	printf("timer_tick\n\r");
	--current->counter;
	if (current->counter<=0 || current->preempt_count <= 0)
	{
		current->counter=0;
		enable_irq();
		_schedule();
		disable_irq();
	}
	
}