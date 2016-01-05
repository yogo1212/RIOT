/**
 * @ingroup     boards_cc2650stk
 * @{
 *
 * @file
 * @brief       peripheral MCU configuration for the CC2650STK board
 *
 * @author      Leon M. George <leon@georgemail.eu>
 */

#ifndef PERIPH_CONF_H_
#define PERIPH_CONF_H_

#include "cc26x0-timer.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name timer peripheral configuration
 * @{
 */
#define TIMER_NUMOF         GPTIMER_NUMOF
#define TIMER_0_EN          1
#define TIMER_1_EN          0
#define TIMER_2_EN          0
#define TIMER_3_EN          0

#define TIMER_IRQ_PRIO      1

/* Timer 0 configuration */
#define TIMER_0_DEV         GPTIMER0
#define TIMER_0_CHANNELS    NUM_CHANNELS_PER_GPTIMER
#define TIMER_0_MAX_VALUE   0xffffffff
#define TIMER_0_IRQn_1      GPTIMER_0A_IRQn
#define TIMER_0_IRQn_2      GPTIMER_0B_IRQn
#define TIMER_0_ISR_1       isr_timer0_chan0
#define TIMER_0_ISR_2       isr_timer0_chan1
/** @} */


/**
 * @name UART configuration
 * @{
 */
#define UART_NUMOF          1

#define UART_0_EN           1
#define UART_1_EN           0
#define UART_2_EN           0
#define UART_3_EN           0

#define UART_IRQ_PRIO       1

/* UART 0 device configuration */
#define UART_0_IRQ          UART0_IRQN
#define UART_0_ISR          isr_uart
/* UART 0 pin configuration */
#define UART_0_RX_DIO       DIO_28_num
#define UART_0_TX_DIO       DIO_29_num
/** @} */

/**
 * @name Random Number Generator configuration
 * @{
 */
#define RANDOM_NUMOF        0 /* TODO has random-shit */
/** @} */

/**
 * @name GPIO configuration
 * @{
 */
#define GPIO_IRQ_PRIO       1

#define GPIO_0_EN           1
#define GPIO_1_EN           1
#define GPIO_2_EN           1
#define GPIO_3_EN           1
#define GPIO_4_EN           1
#define GPIO_5_EN           1
#define GPIO_6_EN           1
#define GPIO_7_EN           1
#define GPIO_8_EN           1
#define GPIO_9_EN           1
#define GPIO_10_EN          1
#define GPIO_11_EN          1
#define GPIO_12_EN          1
#define GPIO_13_EN          1
#define GPIO_14_EN          1
#define GPIO_15_EN          1
#define GPIO_16_EN          1
#define GPIO_17_EN          1
#define GPIO_18_EN          1
#define GPIO_19_EN          1
#define GPIO_20_EN          1
#define GPIO_21_EN          1
#define GPIO_22_EN          1
#define GPIO_23_EN          1
#define GPIO_24_EN          1
#define GPIO_25_EN          1
#define GPIO_26_EN          1
#define GPIO_27_EN          1
#define GPIO_28_EN          1
#define GPIO_29_EN          1
#define GPIO_30_EN          1
#define GPIO_31_EN          1
/** @} */

#ifdef __cplusplus
} /* end extern "C" */
#endif

#endif /* PERIPH_CONF_H_ */
/** @} */
