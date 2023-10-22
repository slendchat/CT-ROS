#include "common.h"
#include "irq.h"
#include "reboot.h"

void soft_reboot()
{
    // Disable interrupts
    disable_irq();
    // Trigger the reboot
    uint32_t *pm_wdog = (uint32_t *)PM_WDOG;
    uint32_t *pm_rstc = (uint32_t *)PM_RSTC;
    uint32_t *pm_rsts = (uint32_t *)PM_RSTS;

    // Power off the system (full reset)
    *pm_rstc = (PM_PASSWORD | PM_RSTC_WRCFG_FULL_RESET);

    // Wait for the system to reset
    while (1);
}
