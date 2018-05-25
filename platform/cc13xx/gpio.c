/*
 * Copyright (c) 2016 Brian Swetland
 * Copyright 2018 The DEOS Authors
 */

#include <dev/gpio.h>

#include <driverlib/gpio.h>
#include <driverlib/ioc.h>

int gpio_config(unsigned nr, unsigned flags) {
	if (flags & GPIO_INPUT) {
		IOCPortConfigureSet(nr, IOC_PORT_GPIO, IOC_INPUT_ENABLE);
	} else {
		IOCPortConfigureSet(nr, IOC_PORT_GPIO, 0);
	}
	if (flags & GPIO_OUTPUT) {
		GPIO_setOutputEnableDio(nr, GPIO_OUTPUT_ENABLE);
	} else {
		GPIO_setOutputEnableDio(nr, GPIO_OUTPUT_DISABLE);
	}
	return 0;
}

void gpio_set(unsigned nr, unsigned on) {
	GPIO_writeDio(nr, on);
}

int gpio_get(unsigned nr) {
	return GPIO_readDio(nr);
}
