#ifndef __PLATFORM_STM32_GPIO_H
#define __PLATFORM_STM32_GPIO_H

#include <stm32f0xx.h>

/* helper defines for STM32 platforms */

/* flag to gpio_configure */
#define GPIO_STM32_AF (0x1 << 16)
#define GPIO_STM32_OD (0x2 << 16)
#define GPIO_STM32_AFn(n) ((n) << 24)

/* gpio port/pin is packed into a single unsigned int in 16x:8port:8pin format */
#define GPIO(port, pin) ((unsigned int)(((port) << 8) | (pin)))

#define GPIO_PORT(gpio) (((gpio) >> 8) & 0xff)
#define GPIO_PIN(gpio) ((gpio) & 0xff)
#define GPIO_AFNUM(gpio) (((gpio) >> 24) & 0xf)

#ifdef GPIOA
#define GPIO_PORT_A 0
#endif
#ifdef GPIOB
#define GPIO_PORT_B 1
#endif
#ifdef GPIOC
#define GPIO_PORT_C 2
#endif
#ifdef GPIOD
#define GPIO_PORT_D 3
#endif
#ifdef GPIOE
#define GPIO_PORT_E 4
#endif
#ifdef GPIOF
#define GPIO_PORT_F 5
#endif

#endif

