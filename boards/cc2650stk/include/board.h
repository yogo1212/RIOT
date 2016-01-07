/**
 * @defgroup    boards_cc2650stk CC2650STK
 * @ingroup     boards
 * @brief       SimpleLink™ CC2650 sensor tag
 * @{
 *
 * @author      Leon M. George <leon@georgemail.eu>
 */

#ifndef BOARD_H_
#define BOARD_H_

#include "cpu.h"
#include "periph/gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * define the nominal CPU core clock in this board
 */
#define F_CPU               XOSC32M_FREQ

/**
 * @name define UART device and baudrate for stdio
 * @{
 */
#define STDIO               UART_0
#define STDIO_BAUDRATE      115200
#define STDIO_RX_BUFSIZE    (64U)
/** @} */

/**
 * @name macros for controlling the on-board LEDs.
 * @{
 */
#define LED_RED_DIO         10
#define LED_GREEN_DIO       15

#define LED_RED_ON          gpio_set(LED_RED_DIO)
#define LED_RED_OFF         gpio_clear(LED_RED_DIO)
#define LED_RED_TOGGLE      gpio_toggle(LED_RED_DIO)

#define LED_GREEN_ON        gpio_set(LED_GREEN_DIO)
#define LED_GREEN_OFF       gpio_clear(LED_GREEN_DIO)
#define LED_GREEN_TOGGLE    gpio_toggle(LED_GREEN_DIO)
/** @} */

/**
 * @name customer configuration (CCFG)
 * @{
 */
#define CCA_BACKDOOR_ENABLE       1
#define CCA_BACKDOOR_PORT_A_PIN   3 /**< Select button */
#define CCA_BACKDOOR_ACTIVE_LEVEL 0 /**< Active low */
/** @} */

/**
 * @brief initialize board specific hardware(LEDs, GPIO)
 */
void board_init(void);

#ifdef __cplusplus
} /* end extern "C" */
#endif

#endif /* BOARD_H_ */
/** @} */
