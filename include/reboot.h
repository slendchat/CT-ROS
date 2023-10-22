#pragma once
#include "peripherals/base.h"

// Address of the watchdog timer control register
#define PM_WDOG_BASE (PBASE + 0x001000)
#define PM_PASSWORD 0x5a000000
#define PM_RSTC     (PM_WDOG_BASE + 0x1c)
#define PM_RSTS     (PM_WDOG_BASE + 0x20)
#define PM_WDOG     (PM_WDOG_BASE + 0x24)

// Magic values for reboot
#define PM_RSTC_WRCFG_FULL_RESET 0x00000020
#define PM_PASSWORD_MASK         0x00ffffff

void soft_reboot();