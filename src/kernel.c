// #include "funcs/uart.h"
// #include "funcs/printf.h"
// #include "funcs/utils.h"
// #include "funcs/int.h"
// #include "funcs/int_enable.h"
// #include "funcs/local_timer.h"
// #include "funcs/timer.h"
// #include "gpio.h"



#include "funcs/utils.h"
#include "funcs/uart.h"
#include "funcs/printf.h"
#include "funcs/int_enable.h"
#include "funcs/int.h"
#include "funcs/local_timer.h"
#include "funcs/timer.h"
#include "funcs/gpio.h"
#include "funcs/fork.h"
#include "funcs/panic.h"

#include "structures/sched.h"
#include "structures/common.h"



void process(char *array)
{
	while (1){
		for (int i = 0; i < 5; i++){
			uart_putc(array[i]);
			delay(100000);
		}
	}
}


void prove_working()
{
    gpio_pin_enable(21);
    gpio_pin_set_func(21,output);
    gpio_pin_set(21);
    delay(1000000);
    gpio_pin_clr(21);
}
void welcomeScreen()
{
    char *welcome = "\n\r░█░█░█▀▀░█░░░█▀▀░█▀█░█▄█░█▀▀░░░▀█▀░█▀█░░░█▀▄░█▀█░▀█▀░░░█▀█░█▀▀\n\r░█▄█░█▀▀░█░░░█░░░█░█░█░█░█▀▀░░░░█░░█░█░░░█▀▄░█▀▀░░█░░░░█░█░▀▀█\n\r░▀░▀░▀▀▀░▀▀▀░▀▀▀░▀▀▀░▀░▀░▀▀▀░░░░▀░░▀▀▀░░░▀░▀░▀░░░▀▀▀░░░▀▀▀░▀▀▀\n\r";
    char *cat_sleepin = "      |\\      _,,,---,,_\n\rZZZzz /,`.-'`'    -.  ;-;;,_\n\r     |,4-  ) )-,_. ,\\ (  `'-'\n\r    '---''(_/--'  `-'\\_)  ARTHUR's General Purpose OS\n\rart by Felix Lee\n\r";
    printf(welcome);
    printf("\n\n\r");
    printf(cat_sleepin);
    printf("\n\n\r");
    printf("Raspberry PI General Purpose OS initializing...\n\r");
    printf("Board[ RPI 3B+ ]\n\r");
    printf("Exception Level[ %d ]\n\r",get_el());
    printf("Process ID[ %d ]\n\r",get_pid());
    printf("Initializing...\n\n\r");
}
int kernel_main()
{
    prove_working();

    uart_init(115200);
    // uart_puts("[UART INITIALIZED]\n\r");

    init_printf(0,uart_char_printf);
    // printf("[printf INITIALIZED]\n\n\n\n\r");

    welcomeScreen();

    int_vector_init();
    printf("[irq vector table init]\n\r");

    timer_init();
    printf("[timer initialized]\n\r");

    enable_interrupt_controller();
    printf("[enable interrupt controller]\n\r");

    enable_irq();
    printf("[interrupts enabled]\n\r");

    // loc_timer_init(0x0ffffff);
    // printf("[LOCAL TIMER initialized]\n\r");

    task_init();
    printf("[first task init]\n\r");

    // printf("200\n\r");
    // timer_sleep(200);
    // printf("300\n\r");
    // timer_sleep(300);
    // printf("4000\n\r");
    // timer_sleep(4000);
    // printf("5000\n\r");
    // timer_sleep(5000);
    // printf("600\n\r");
    // timer_sleep(600);
    // printf("done\n\r");
    

	int res = copy_process((unsigned long)&process, (unsigned long)"12345");
	if (res != 0) {
		printf("error while starting process 1");
        panic();
	}
	res = copy_process((unsigned long)&process, (unsigned long)"abcde");
	if (res != 0) {
		printf("error while starting process 2");
		panic();
	}


    for (int i = 0; i < NR_TASKS; i++)
    {
        if (task[i]!=NULL)
        {
            printf("task[%d] pid=[%d] and cntr =[%d]\n\r",i,task[i]->pid,task[i]->counter);
        }
        
    }
    
    while (1)
    {
        schedule();
        delay(1000000);
    for (int i = 0; i < NR_TASKS; i++)
        {   
        if (task[i]!=NULL)
        {
            printf("task[%d] pid=[%d] and cntr =[%d]\n\r",i,task[i]->pid,task[i]->counter);
        }
        
        }
    }
    
}