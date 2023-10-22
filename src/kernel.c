
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
#include "i2c.h"
#include "sigfun.h"
#include "reboot.h"


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
	// u8 data = 3;
	// while (1)
	// {
    // 	i2c_send(21,&data,1);
	// 	printf("sent %d\n\r",data);
	// 	schedule();
	// }
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
void kernel_threadD()
{
	for (int i = 0; i < 100; i++)
	{
		printf("[%d] iterations untill process 3 will be terminated\n\r",i);
		delay(100000);
	}
	printf("kill");
	kill(3,SIGTERM);
	printf("exit");
	exit_process();
	
}
void kernel_threadE()
{
	reprior(20,get_id());
	gpio_pin_enable(16);
    gpio_pin_set_func(16,output);
    while (1)
    {
        gpio_pin_set(16);
        delay(500000);  
        gpio_pin_clr(16);
        delay(500000);
    }
     
}

void kernel_main()
{
	
	
	uart_init(115200);
	init_printf(NULL, uart_char_printf);
	welcomeScreen();
	// i2c_init();
	// for (int i = 0; i < 10; i++)
	// {
	// 	char buf[10];
	// 	i2c_recv(21,buf,9);
	// 	buf[9]=0;
	// 	printf("%s\n\r",buf);
	// 	timer_sleep(250);
	// }
	// for (u8 d = 1; d < 10; d++)
	// {
	// 	i2c_send(21,&d,1);
	// 	timer_sleep(250);
	// 	printf("sent %d\n\r",d);
	// }
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

	// r = copy_process(PF_KTHREAD, (unsigned long)&kernel_threadB, 0);
	// if (r < 0) {
	// 	printf("error while starting kernel process");
	// 	return;
	// }

	r = copy_process(PF_KTHREAD, (unsigned long)&kernel_threadC, 0);
	if (r < 0) {
		printf("error while starting kernel process");
		return;
	}
	r = copy_process(PF_KTHREAD, (unsigned long)&kernel_threadD, 0);
	if (r < 0) {
		printf("error while starting kernel process");
		return;
	}
	r = copy_process(PF_KTHREAD, (unsigned long)&kernel_threadE, 0);
	if (r < 0) {
		printf("error while starting kernel process");
		return;
	}
	r = copy_process(PF_KTHREAD, (unsigned long)&kernel_threadB, 0);
	if (r < 0) {
		printf("error while starting kernel process");
		return;
	}
	
	int j = 0;
	while (1){
		for (int i = 0; i < NR_TASKS; i++)
		{
			if (task[i]!=NULL)
			{
				printf("task [%d] exists | state[%d]\n\r",task[i]->pid,task[i]->state);
			}
		}
		printf("%d\n\r",j);
		if(++j==10)
			soft_reboot();		
		printf("main\n\r");
		schedule();
	}	
}
