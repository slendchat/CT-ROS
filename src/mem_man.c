#include "constants/memory.h"
#include "structures/common.h"

static u16 mem_map[PAGING_PAGES] = {0}; // 257024 pages at all and 16 bits are enough to store all of their numbers

u64 get_free_page()
{
    for (int i = 0; i < PAGING_PAGES; i++)
    {
        if (mem_map[i]==0)
        {
            mem_map[i]=1;
            return (LOW_MEMORY + i*PAGE_SIZE);
        }
    }    
    return 0;
}

void free_page(u64 page)
{
    mem_map[(page-LOW_MEMORY)/PAGE_SIZE]=0;
}