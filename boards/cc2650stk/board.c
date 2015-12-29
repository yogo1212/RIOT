/**
 * @ingroup     boards_cc2650stk
 * @{
 *
 * @file
 * @brief       Board specific implementations for the CC2650STK board
 *
 * @author      Leon M. George <leon@georgemail.eu>
 */

#include <stdio.h>

#include "board.h"
#include "cpu.h"

#include "cc26x0-ioc.h"
#include "cc26x0-gpio.h"

static void led_init(void)
{
    IOCFG_n(LED_RED_DIO) = IOCFG_QUICK_OUTPUT;
    IOCFG_n(LED_GREEN_DIO) = IOCFG_QUICK_OUTPUT;
}

static void sleep(uint32_t s)
{

}

/**
 * @brief Initialize the SmartRF06 board
 */
void board_init(void)
{
    /* initialize the CPU */
    cpu_init();

    /* initialize the boards LEDs */
    led_init();


    while (true) {
        LED_GREEN_TOGGLE;
        sleep(10);
    }
}

/** @} */
