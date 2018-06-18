#ifndef __PLATFORM_STM32_GPIO_H
#define __PLATFORM_STM32_GPIO_H

/* helper defines for STM32 platforms */

/* flag to gpio_configure */
#define GPIO_STM32_AF (0x1 << 16)
#define GPIO_STM32_OD (0x2 << 16)
#define GPIO_STM32_AFn(n) ((n) << 24)

/* gpio port/pin is packed into a single unsigned int in 16x:8port:8pin format */
#define GPIO(port, pin) ((unsigned int)(((port) << 8) | (pin)))

#define GPIO_TO_PIN_MASK(gpio) ((unsigned int)( 1 << ((gpio) & 0x0f)))

#define GPIO_PORT(gpio) (((gpio) >> 8) & 0xff)
#define GPIO_PIN(gpio) ((gpio) & 0xff)
#define GPIO_AFNUM(gpio) (((gpio) >> 24) & 0xf)

#define GPIO_PORT_A 0
#define GPIO_PORT_B 1
#define GPIO_PORT_C 2
#define GPIO_PORT_D 3
#define GPIO_PORT_E 4
#define GPIO_PORT_F 5
#define GPIO_PORT_G 6
#define GPIO_PORT_H 7
#define GPIO_PORT_I 8
#define GPIO_PORT_J 9
#define GPIO_PORT_K 10

#endif

