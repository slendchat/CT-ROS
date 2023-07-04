#include "peripherals/gpio_regs.h"
#include "funcs/utils.h"
#include "funcs/gpio.h"

void gpio_pin_set_func(u8 pin,gpio_funcs func)
{
    u8 pin_pos = (pin * 3) % 30;
    u8 fsel_reg = pin / 10;
    u32 selector = REGS_GPIO->gpfsel[fsel_reg];

    selector &= ~(0b111 << pin_pos);
    selector |= (func << pin_pos);     

    REGS_GPIO->gpfsel[fsel_reg] = selector;
}
void gpio_pin_enable(u8 pin)
{
    REGS_GPIO->gppud_en = 0;
    delay(155);
    REGS_GPIO->gppudclk[pin/32] = (1 << (pin % 32));
    delay(155);
    REGS_GPIO->gppud_en = 0;
    REGS_GPIO->gppudclk[pin/32] = 0;
}
void gpio_pin_set(u8 pin)
{
    REGS_GPIO->gpset.data[pin/32] = (1 << (pin % 32));
}
void gpio_pin_clr(u8 pin)
{
    REGS_GPIO->gpclr.data[pin/32] = (1 << (pin % 32));
}