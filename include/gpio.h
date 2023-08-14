#pragma once
#include "common.h"

typedef enum _gpio_funcs
{
    input = 0b0,
    output = 0b1,
    alt0 = 0b100,
    alt1 = 0b101,
    alt2 = 0b110,
    alt3 = 0b111,
    alt4 = 0b011,
    alt5 = 0b010
}gpio_funcs;

void gpio_pin_set_func(u8 pin,gpio_funcs func);
void gpio_pin_enable(u8 pin);
void gpio_pin_set(u8 pin);
void gpio_pin_clr(u8 pin);