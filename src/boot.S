#include "arm/sysregs.h"
#include "arm/mmu.h"
#include "mm.h"
#include "peripherals/base.h"
.section ".text.boot"
.global _start
_start:
    mrs x0,mpidr_el1
    and x0,x0,0xff
    cbz x0,switch_toel1
    b proc_hang

switch_toel1:

    ldr x0,=SCTLR_VALUE_MMU_DISABLED
    msr sctlr_el1, x0

    ldr x0,=HCR_VALUE
    msr hcr_el2, x0

    ldr x0,=SCR_VALUE
    msr scr_el3, x0

    ldr x0,=SPSR_VALUE
    msr spsr_el3,x0

    adr x0,el1_begin
    msr elr_el3,x0
    
    eret

el1_begin:
	adr	x0, bss_begin
	adr	x1, bss_end
	sub	x1, x1, x0
	bl 	memzero

    bl create_PT_init

    mov x0, #VA_START
    add sp,x0,#LOW_MEMORY
    // Store the location of the translation table in ttbr1_el1
    adrp x0,pg_dir          
    msr ttbr1_el1,x0

    // granularity and max size
    ldr x0,=TCR_VAL
    msr tcr_el1,x0

    //memory settings  like non cacheable or device mem
    ldr x0,=MAIR_VAL
    msr mair_el1,x0

    ldr x2,=kernel_main

    mov x0,#SCTLR_MMU_ENABLED
    msr sctlr_el1, x0

    br x2

create_PT_init:
    mov x29,x30 //keep return addr
    adrp x0, pg_dir //pg_dir mentioned in linker
    mov x1, #PG_DIR_SIZE
    bl memzero

    adrp x0, pg_dir
    mov x1,#VA_START

    //***************************create PGD | table virt_base 

    lsr x2,x1,#PGD_SHIFT
    and x2,x2,#PTRS_PER_TABLE - 1
    //basically we stripped everything to right 39 and left (higher than 0b11111111) 
    add x3,x0,#PAGE_SIZE
    //calculating next page_table
    orr x3,x3,#0x3
    //table descriptor must has 2 lower bits 1

    str x3,[x0,x2,lsl #3]
    // store x3: base x0 offset x2 << 3
    add x0,x0,#PAGE_SIZE

    //***************************create PUD*******************

    lsr x2,x1,#PUD_SHIFT
    and x2,x2,#PTRS_PER_TABLE - 1
    //basically we stripped everything to right 30 and left (higher than 0b11111111) 
    add x3,x0,#PAGE_SIZE
    //calculating next page_table
    orr x3,x3,#0x3
    //table descriptor must has 2 lower bits 1

    str x3,[x0,x2,lsl #3] // str x3 to x0+8*x2
    // store x3: base x0 offset x2 << 3
    add x0,x0,#PAGE_SIZE

    // MAPPING KERNEL STACK
    mov x1,xzr
    mov x2,#VA_START
    ldr x3, =(VA_START+DEVICE_BASE-SECTION_SIZE) //last virtaddr

    // x0 tbl, x1 phys, x2 start, x3 end, x4 tmp
    lsr    x2, x2, #SECTION_SHIFT
    and    x2, x2, #PTRS_PER_TABLE - 1            // table index
    lsr    x3, x3, #SECTION_SHIFT
    and    x3, x3, #PTRS_PER_TABLE - 1                // table end index
    lsr    x1, x1, #SECTION_SHIFT
    ldr    x4, =MMU_LOWER_ATTR_NM
    orr    x1, x4, x1, lsl #SECTION_SHIFT            // table entry
loop1:    
    str    x1, [x0, x2, lsl #3]                // store the entry
    add    x2, x2, #1                    // next entry
    add    x1, x1, #SECTION_SIZE                // next block
    cmp    x2, x3
    b.ls    loop1

    //mapping device memory
    mov x1,#DEVICE_BASE
    ldr x2,=(VA_START+DEVICE_BASE)
    ldr x3,=(VA_START + PHYS_MEMORY_SIZE-SECTION_SIZE)

    // x0 tbl, x1 phys, x2 start, x3 end, x4 tmp
    lsr    x2, x2, #SECTION_SHIFT
    and    x2, x2, #PTRS_PER_TABLE - 1            // table index
    lsr    x3, x3, #SECTION_SHIFT
    and    x3, x3, #PTRS_PER_TABLE - 1                // table end index
    lsr    x1, x1, #SECTION_SHIFT
    ldr    x4, =MMU_LOWER_ATTR_DEV
    orr    x1, x4, x1, lsl #SECTION_SHIFT            // table entry
loop2:    
    str    x1, [x0, x2, lsl #3]                // store the entry
    add    x2, x2, #1                    // next entry
    add    x1, x1, #SECTION_SIZE                // next block
    cmp    x2, x3
    b.ls    loop2

    mov x30,x29
    ret

proc_hang:
    b proc_hang