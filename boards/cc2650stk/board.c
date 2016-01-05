/**
 * @ingroup     boards_cc2650stk
 * @{
 *
 * @file
 * @brief       Board specific implementations for the CC2650STK board
 *
 * @author      Leon M. George <leon@georgemail.eu>
 */

#include "board.h"
#include "cpu.h"

#include "cc26x0-ioc.h"
#include "cc26x0-gpio.h"
#include "cc26x0-prcm.h"

static void led_init(void)
{
    IOC->CFG[LED_RED_DIO] = 0;//IOCFG_QUICK_OUTPUT;
    IOC->CFG[LED_GREEN_DIO] = 0;//IOCFG_QUICK_OUTPUT;
    GPIO->DOE = ((1 << LED_RED_DIO) | (1 << LED_GREEN_DIO));

    GPIO->DOUTSET = (1 << LED_RED_DIO);
    GPIO->DOUTCLR = (1 << LED_GREEN_DIO);
}

static void _gpio_init(void)
{
    PRCM->PDCTL0 |= PDCTL0_PERIPH_ON;
    while(!(PRCM->PDSTAT0 & PDSTAT0_PERIPH_ON)) ;

    PRCM->GPIOCLKGR |= 1;
    PRCM->CLKLOADCTL |= CLKLOADCTL_LOAD;
    while (!(PRCM->CLKLOADCTL & CLKLOADCTL_LOADDONE)) ;
}

static void sleep(uint32_t s)
{
    while (s-- > 0) {
        __asm__ volatile (
            "nop\n\t"
            "nop\n\t"
            "nop\n\t"    );
    }
}

/**
 * @brief Initialize the SmartRF06 board
 */
void board_init(void)
{
    /* initialize the CPU */
    cpu_init();

    _gpio_init();

    /* initialize the boards LEDs */
    led_init();

    while (true) {
        GPIO->DOUTTGL = (1 << LED_RED_DIO) | (1 << LED_GREEN_DIO);
        sleep(1000000);
    }
}

/** @} */
