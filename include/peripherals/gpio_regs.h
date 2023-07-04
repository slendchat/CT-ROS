#pragma once

#include "structures/common.h"
#include "peripherals/base.h"

struct  gpioPinData
{
    reg32 reserved;
    reg32 data[2];
};
struct gpio_regs
{
    reg32 gpfsel[6];
    struct gpioPinData gpset;
    struct gpioPinData gpclr;
    struct gpioPinData gplev;
    struct gpioPinData gpeds;
    struct gpioPinData gpren;
    struct gpioPinData gpfen;
    struct gpioPinData gphen;
    struct gpioPinData gplen;
    struct gpioPinData gparen;
    struct gpioPinData gpafen;
    reg32 reserved;
    reg32 gppud_en;
    reg32 gppudclk[2];
};

#define REGS_GPIO ((struct gpio_regs*)(PBASE + 0x200000))