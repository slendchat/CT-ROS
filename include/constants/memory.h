#pragma once
#include "peripherals/base.h"

#define S_FRAME_SIZE 272 // size of all saved registers

#define PAGE_SHIFT 12 // 1 << 12 = 4096 = 4KB
#define TABLE_SHIFT 10 // 1 << 10 idk what is it 1024
#define SECTION_SHIFT (PAGE_SHIFT + TABLE_SHIFT)// 1 << 22 also idk 4mb

#define PAGE_SIZE (1<<PAGE_SHIFT)
#define SECTION_SIZE (1<<SECTION_SHIFT)

#define HIGH_MEMORY PBASE // after 0x3F000000 there is IO mapped 
#define LOW_MEMORY (SECTION_SIZE) //4mb

#define PAGING_MEMORY (HIGH_MEMORY - LOW_MEMORY)
#define PAGING_PAGES (PAGING_MEMORY / PAGE_SIZE)

#ifndef __ASSEMBLER__

#include "structures/common.h"
u64 get_free_page();
void free_page(u64 page);
extern void memzero(u64 src, u64 len);

#endif