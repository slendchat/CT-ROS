.global get_el
get_el:
    mrs x0, CurrentEL
    lsr x0,x0,#2
    ret

.global get_pid
get_pid:
    mrs x0, mpidr_el1
    and x0,x0,#3
    ret

.global delay
delay:
    subs x0,x0,#1
    bne delay
    ret

.global read32
read32:
    ldr w0,[x0]
    ret

.global write32
write32:
    str w1,[x0]
    ret