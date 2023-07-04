#include "arm/ctrl_vals.h"
#include "constants/memory.h"
.section ".text.boot"

.global _start
_start:
    mrs x0, mpidr_el1
    and x0,x0,#3
    cbz x0, master      //shouldnt return
    b proc_hang     //to be sure if return it wouldnt do initialization

                    // el3 secure monitor | el2 hypervisor
master:             // el1 OS kernel      | el0 applications
    bl goto_el2    // drop to el2
    bl goto_el1    // drop to el1

    adr x0, bss_begin
    adr x1, bss_end
    sub x1,x1,x0
    bl memzero

    mov sp, #SECTION_SIZE

    bl kernel_main

    b proc_hang

goto_el2:
    ldr x0, =SCTRL_EL2_VAL
    msr sctlr_el2,x0

    ldr x0, =HCR_EL2_VAL
    msr hcr_el2,x0

    ldr x0, =SCR_VAL
    msr scr_el3,x0

    ldr x0, =SPSR_EL2_VAL
    msr spsr_el3,x0

    mov x0, lr
    msr elr_el3,x0

    eret
goto_el1:
    ldr x0, =SCTRL_EL1_VAL
    msr sctlr_el1,x0

    ldr x0, =SPSR_EL1_VAL
    msr spsr_el2,x0

    ldr x0, =CPACR_VAL      //disabling trap for SIMDunit and FPunit
    msr cpacr_el1,x0    

    mov x0, lr
    msr elr_el2,x0

    eret
create_page_tables:
    ret
proc_hang: b proc_hang
