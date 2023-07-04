#pragma once
#include "structures/common.h"
extern void ret_from_fork(void);
int copy_process (u64 fn, u64 arg);