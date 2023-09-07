#ifndef	_SYS_H
#define	_SYS_H

#define __NR_syscalls	 5

#ifndef __ASSEMBLER__
#include "common.h"
void sys_write(char * buf);
int sys_fork();
void sys_exit();
void sys_reprior(u32 prior, u32 id);
void sys_kill(long pid,SIGNALS sig);
#endif

#endif  /*_SYS_H */
