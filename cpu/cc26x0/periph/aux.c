#include "cc26x0-aux.h"

bool addi_reg_access_prepare(void)
{
    bool ie = !__get_PRIMASK();
    __disable_irq();
    while (!ADDI_SEM);
    return ie;
}

void addi_reg_acces_finish(bool ie)
{
    ADDI_SEM = 1;
    if (ie) {
        __enable_irq();
    }
}