#ifndef	_SYS_H
#define	_SYS_H

#define __NR_syscalls	 4

#ifndef __ASSEMBLER__
#include "common.h"
void sys_write(char * buf);
int sys_fork();
void sys_reprior(u32 prior, u32 id);
#endif

#endif  /*_SYS_H */
