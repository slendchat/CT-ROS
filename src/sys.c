#include "fork.h"
#include "printf.h"
#include "utils.h"
#include "sched.h"
#include "mm.h"
#include "common.h"
#include "sigfun.h"


void sys_write(char * buf){
	printf(buf);
}

int sys_fork(){
	return copy_process(0, 0, 0);
}

void sys_exit(){
	exit_process();
}
void sys_reprior(u32 prior, u32 id)
{
	reprior(prior,id);
}
void sys_kill(long pid,SIGNALS sig)
{
	kill(pid,sig);
}


void * const sys_call_table[] = {sys_write, sys_fork, sys_exit,sys_reprior,sys_kill};
