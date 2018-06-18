/*
 * Copyright (c) 2015 MediaTek Inc.
 * Copyright 2018 The DEOS Authors
 */
#ifndef _MT_GIC_H_
#define _MT_GIC_H_

#include "platform/mt_irq.h"

#define IRQ_REGS    ((NR_IRQ_LINE + (32 - 1)) >> 5)

enum {IRQ_MASK_HEADER = 0xF1F1F1F1, IRQ_MASK_FOOTER = 0xF2F2F2F2};

struct mtk_irq_mask {
    unsigned int header;   /* for error checking */
    unsigned int mask[IRQ_REGS];
    unsigned int footer;   /* for error checking */
};

int mt_irq_mask_all(struct mtk_irq_mask *mask); //(This is ONLY used for the sleep driver)
int mt_irq_mask_restore(struct mtk_irq_mask *mask); //(This is ONLY used for the sleep driver)
void mt_irq_set_sens(unsigned int irq, unsigned int sens);
void mt_irq_set_polarity(unsigned int irq, unsigned int polarity);
void mt_irq_mask(unsigned int irq);
void mt_irq_unmask(unsigned int irq);
uint32_t mt_irq_get(void);
void mt_irq_ack(unsigned int irq);

void platform_init_interrupts(void);
void platform_deinit_interrupts(void);
void mt_irq_register_dump(void);

#endif /* !_MT_GIC_H_ */

