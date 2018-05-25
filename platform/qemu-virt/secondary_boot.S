/*
 * Copyright (c) 2014 Travis Geiselbrecht
 * Copyright 2018 The DEOS Authors
 */

#include <asm.h>

.section .text

/* used to call into PSCI firmware (Power State Coordination Firmware) */
FUNCTION(psci_call)
    hvc     #0
#if ARCH_ARM
    bx      lr
#else
    ret
#endif

.ltorg

