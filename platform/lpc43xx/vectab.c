/*
 * Copyright (c) 2015 Brian Swetland
 * Copyright 2018 The DEOS Authors
 */

#include <debug.h>
#include <compiler.h>
#include <arch/arm/cm.h>

void lpc43xx_dummy_irq(void)
{
    arm_cm_irq_entry();
    panic("unhandled irq\n");
}

// default handlers are weak aliases to the dummy handler
#define DEFIRQ(x) \
    void lpc43xx_##x##_IRQ(void) __WEAK_ALIAS("lpc43xx_dummy_irq");
#include <platform/defirq.h>
#undef DEFIRQ

#define DEFIRQ(x) [x##_IRQn] = lpc43xx_##x##_IRQ,
const void *const __SECTION(".text.boot.vectab2") vectab2[] = {
#include <platform/defirq.h>
};
#undef DEFIRQ
