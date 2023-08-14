//ttbr0_el1 page 2726
//ttbr0_el1 ttbr1_el1
//TCR_EL1 page 2685
#pragma once
//armv8 manual page 2609

// indexes for block descriptors
//nG means that reads performs as many as pending, no cache can be returned
//nR means no reordering in device accesses
//nE means write response must come from the peripheral. 
#define MT_DEVICE_nGnRnE 0x0 

// normal memory non cacheable
#define MT_NORMAL_NC     0x1 

#define MT_DEVICE_nGnRnE_FLAGS 0x00

// 1000|100 means 100 means normal inner noncacheable memory
//1000 means Normal memory, Outer Write-Through Non-transient
#define MT_NORMAL_NC_FLAGS 0b1000100  

#define MAIR_VAL (MT_DEVICE_nGnRnE_FLAGS << (8 * MT_DEVICE_nGnRnE) | MT_NORMAL_NC_FLAGS << (8 * MT_NORMAL_NC))

//the size offset of mem reg addressed by ttbr0. 2^(64-TOSZ)
#define TCR_T0SZ (64 - 48)

// granularity, 0b00 means 4kb
#define TCR_TG0 (0b00 << 14)

//the size offset of mem reg addressed by ttbr1. 2^(64-TOSZ)
#define TCR_T1SZ ((64-48) << 16)

#define TCR_TG1 (0b00 << 30)

#define TCR_VAL (TCR_T0SZ | TCR_TG0 | TCR_T1SZ | TCR_TG1)



#define MM_TYPE_PAGE_TABLE		0b11
#define MM_TYPE_PAGE 			0b11
#define MM_TYPE_BLOCK			0b1
#define MM_ACCESS			    (0x1 << 10)
#define MM_ACCESS_PERMISSION	(0x01 << 6) 



#define MMU_LOWER_ATTR_NM (MM_TYPE_BLOCK | (MT_NORMAL_NC << 2) | MM_ACCESS)

#define MMU_LOWER_ATTR_DEV (MM_TYPE_BLOCK | (MT_DEVICE_nGnRnE << 2) | MM_ACCESS)

#define MMU_PTE_FLAGS	    (MM_TYPE_PAGE | (MT_NORMAL_NC << 2) | MM_ACCESS | MM_ACCESS_PERMISSION)




//                           Descriptor format
//`+------------------------------------------------------------------------------------------+
// | Upper attributes | Address (bits 47:12) | Lower attributes | Block/table bit | Valid bit |
// +------------------------------------------------------------------------------------------+
// 63                 47                     11                 2                 1           0

// bits[4:2]