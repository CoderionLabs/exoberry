/*
 * Copyright (c) 2016 Eric Holland
 * Copyright 2018 The DEOS Authors
 */
#include <err.h>
#include <debug.h>
#include <arch/arm/cm.h>
#include <dev/uart.h>
#include <platform.h>
#include <platform/nrf52.h>
#include <platform/system_nrf52.h>



void platform_early_init(void)
{
    // Crank up the clock before initing timers.
    SystemInit();
    arm_cm_systick_init(32768);
}

void platform_init(void)
{
    dprintf(SPEW, "Nordic nrf52xxx platform for lk...\n");
    dprintf(SPEW, "\tFlash: %d pages of %d bytes each (%dk bytes total)\n", \
            NRF_FICR->CODESIZE, NRF_FICR->CODEPAGESIZE, \
            (NRF_FICR->CODESIZE * NRF_FICR->CODEPAGESIZE)>>10);
    dprintf(SPEW, "\tRadio MAC address  %02x:%02x:%02x:%02x:%02x:%02x\n", \
            (NRF_FICR->DEVICEADDR[1] >> 8) & 0xFF, \
            (NRF_FICR->DEVICEADDR[1]) & 0xFF, \
            (NRF_FICR->DEVICEADDR[0] >> 24) & 0xFF, \
            (NRF_FICR->DEVICEADDR[0] >> 16) & 0xFF, \
            (NRF_FICR->DEVICEADDR[0] >>  8) & 0xFF, \
            (NRF_FICR->DEVICEADDR[0] >>  0) & 0xFF);
}
