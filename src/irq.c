#include "utils.h"
#include "printf.h"
#include "timer.h"
#include "entry.h"
#include "common.h"
#include "peripherals/irq.h"
#include "peripherals/aux_regs.h"
#include "uart.h"
#include "console.h"

const char *entry_error_messages[] = {
	"SYNC_INVALID_EL1t",
	"IRQ_INVALID_EL1t",		
	"FIQ_INVALID_EL1t",		
	"ERROR_INVALID_EL1T",		

	"SYNC_INVALID_EL1h",		
	"IRQ_INVALID_EL1h",		
	"FIQ_INVALID_EL1h",		
	"ERROR_INVALID_EL1h",		

	"SYNC_INVALID_EL0_64",		
	"IRQ_INVALID_EL0_64",		
	"FIQ_INVALID_EL0_64",		
	"ERROR_INVALID_EL0_64",	

	"SYNC_INVALID_EL0_32",		
	"IRQ_INVALID_EL0_32",		
	"FIQ_INVALID_EL0_32",		
	"ERROR_INVALID_EL0_32",

	"SYNC_ERROR",
	"SYSCALL_ERROR"
};


void show_invalid_entry_message(int type, unsigned long esr, unsigned long address)
{
	printf("%s, ESR: %x, address: %x\r\n", entry_error_messages[type], esr, address);
}

void handle_irq()
{
	//printf("\n\rhandle_irq\n\r");
	u32 irq;
	irq = REGS_IRQ->IRQ_PENDING_1;

	// if ((REGS_LOC_TIMER->core[0] & pending_local_timer) == pending_local_timer)
	// {
	// 	handle_loc_timer_irq();
	// }
	
	if (irq & AUX_IRQ)
	{
		irq &= ~AUX_IRQ;
		while ((REGS_AUX->MU_IIR_REG & 4)==4)
		{
			uart_echo();
			// if (cnt < 256)
			// {
				// input_buf[cnt]=uart_getc();
				// cnt++;
			// }
			
		}
	}

	// if(irq & SYSTEM_TIMER_IRQ_3)
	// {
	// 	irq &= ~SYSTEM_TIMER_IRQ_3;
	// 	handle_timer_3_irq();
	// 	// printf("HANDLED TIMER3 IRQ-[%x]\n\n\n\r",irq);
	// }
	if(irq & SYSTEM_TIMER_IRQ_1)
	{
		//printf("HANDLED TIMER1 IRQ-[%x]\n\n\n\r",irq);
		irq &= ~SYSTEM_TIMER_IRQ_1;
		handle_timer_1_irq();
	}
	

}	