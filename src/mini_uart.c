#include "funcs/utils.h"
//#include "peripherals/mini_uart.h"
#include "peripherals/gpio_regs.h"
#include "peripherals/aux_regs.h"
#include "funcs/gpio.h"

int count_baud_reg(int baudrate)
{
    float baud_reg = (250*1000000)/(8*baudrate) - 1;
    int ret =(int) baud_reg;
    return ret;
}

void uart_init(int baudrate)
{
    //set alt5 for gpio14 and gpio15
    gpio_pin_set_func(14,alt5);
    gpio_pin_set_func(15,alt5);

    gpio_pin_enable(14);
    gpio_pin_enable(15);

    REGS_AUX->enables = 1;
    REGS_AUX->MU_CNTL_REG =0;
    REGS_AUX->MU_IER_REG =0;
    REGS_AUX->MU_LCR_REG =3;
    REGS_AUX->MU_MCR_REG =0;
    REGS_AUX->MU_IIR_REG =0xC6;
    REGS_AUX->MU_BAUD_REG =count_baud_reg(baudrate);
    REGS_AUX->MU_IER_REG =0b1101;
    REGS_AUX->MU_CNTL_REG =3;

}
void uart_putc(char c)
{
    while (1){
        if(REGS_AUX->MU_LSR_REG & 0x20)
            break;
    }
    REGS_AUX->MU_IO_REG = c;
    
}
char uart_getc()
{
    while (1)
    {
        if (REGS_AUX->MU_LSR_REG & 0x1)
            break;
    }
    return(REGS_AUX->MU_IO_REG & 0xff);
}
void uart_puts(char* str)
{
    for (int i = 0; str[i] != '\0'; i++){
        uart_putc((char)str[i]);
    }
    
}
void uart_char_printf(void *p, char c)
{
    uart_putc(c);
}
void uart_echo()
{
    uart_putc(uart_getc());
    REGS_AUX->MU_IIR_REG=2;
}