#pragma once

#include "structures/common.h"

struct cpu_context
{
    u64 x19;
    u64 x20;
    u64 x21;
    u64 x22;
    u64 x23;
    u64 x24;
    u64 x25;
    u64 x26;
    u64 x27;
    u64 x28;
    u64 fp;
    u64 sp;
    u64 pc;
};

struct task_struct
{
    struct cpu_context cpu_context;
    u64 state;  //0-runnable -1 unrunnable 0 stopped
    u64 counter;
    u64 priority;
    u64 preempt_count;
    u64 pid;
};

#define INIT_TASK \
/*cpu_context*/	{ {0,0,0,0,0,0,0,0,0,0,0,0,0},0,1,1,0,1}
