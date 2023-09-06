#include "sched.h"
#include "printf.h"

void kill(long pid, SIGNALS sig)
{
    preempt_disable();
    printf("[killing{%d}]",pid);
    for (int i = 0; i < NR_TASKS; i++)
    {
        if (task[i]->pid==pid)
        {
            task[i]->signal.TIF_SIGPENDING=228;
            task[i]->signal.signal=sig;
            break;
        }
    }
}