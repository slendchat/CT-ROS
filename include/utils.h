#pragma once

extern void delay ( unsigned long);
extern void write32 ( unsigned long, unsigned int );
extern unsigned int read32 ( unsigned long );
extern unsigned long get_el ( void );
extern void set_pgd(unsigned long pgd);
extern unsigned long get_pgd();
extern unsigned long get_pid();

