
#include <stdint.h>

#include "printf.h"
#include "utils.h"
#include "timer.h"
#include "irq.h"
#include "fork.h"
#include "sched.h"
#include "uart.h"
#include "sys.h"
#include "user.h"
#include "int_enable.h"
#include "gpio.h"
#include "welcome.h"


void kernel_process(){
	printf("Kernel process started. EL %d\r\n", get_el());
	unsigned long begin = (unsigned long)&user_begin;
	unsigned long end = (unsigned long)&user_end;
	unsigned long process = (unsigned long)&user_process;
	int err = move_to_user_mode(begin, end - begin, process - begin);
	if (err < 0){
		printf("Error while moving process to user mode\n\r");
	} 
}
void kernel_threadA()
{
    while (1)
    {
        printf("A");
		delay(100000);
    }
     
}
void kernel_threadB()
{
    while (1)
    {
        printf("B");
        delay(100000);
    }
     
}
void kernel_threadC()
{
	reprior(40,get_id());
	gpio_pin_enable(21);
    gpio_pin_set_func(21,output);
    while (1)
    {
        gpio_pin_set(21);
        delay(1000000);  
        gpio_pin_clr(21);
        delay(1000000);
    }
     
}

void kernel_main()
{
	uart_init(115200);
	init_printf(NULL, uart_char_printf);
	welcomeScreen();
	irq_vector_init();
	timer_init();
	enable_interrupt_controller();
	enable_irq();
	sched_init();
	
	int r = copy_process(PF_KTHREAD, (unsigned long)&kernel_process, 0);
	if (r < 0) {
		printf("error while starting kernel process");
		return;
	}

	r = copy_process(PF_KTHREAD, (unsigned long)&kernel_threadA, 0);
	if (r < 0) {
		printf("error while starting kernel process");
		return;
	}

	r = copy_process(PF_KTHREAD, (unsigned long)&kernel_threadB, 0);
	if (r < 0) {
		printf("error while starting kernel process");
		return;
	}

	r = copy_process(PF_KTHREAD, (unsigned long)&kernel_threadC, 0);
	if (r < 0) {
		printf("error while starting kernel process");
		return;
	}
	
	for (int i = 0; i < NR_TASKS; i++)
	{
		if (task[i]!=NULL)
		{
			printf("task [%d] exists\n\r",i);
		}
	}
	
	while (1){
		for (int i = 0; i < NR_TASKS; i++)
		{
			if (task[i]!=NULL)
			{
				printf("task [%d] exists\n\r",i);
			}
		}
		printf("main\n\r");
		schedule();
	}	
}
