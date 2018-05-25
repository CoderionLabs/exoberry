/*
 * Copyright (c) 2014-2015 Travis Geiselbrecht
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files
 * (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#include <dev/virtio.h>
#include <dev/virtio/virtio_ring.h>

#include <debug.h>
#include <assert.h>
#include <trace.h>
#include <compiler.h>
#include <list.h>
#include <err.h>
#include <stdlib.h>
#include <string.h>
#include <pow2.h>
#include <lk/init.h>
#include <kernel/thread.h>
#include <kernel/vm.h>
#include <platform/interrupts.h>

#include "virtio_priv.h"

#if WITH_DEV_VIRTIO_BLOCK
#include <dev/virtio/block.h>
#endif
#if WITH_DEV_VIRTIO_NET
#include <dev/virtio/net.h>
#endif
#if WITH_DEV_VIRTIO_GPU
#include <dev/virtio/gpu.h>
#endif

#define LOCAL_TRACE 0

static struct virtio_device *devices;

static void dump_mmio_config(const volatile struct virtio_mmio_config *mmio)
{
    printf("mmio at %p\n", mmio);
    printf("\tmagic 0x%x\n", mmio->magic);
    printf("\tversion 0x%x\n", mmio->version);
    printf("\tdevice_id 0x%x\n", mmio->device_id);
    printf("\tvendor_id 0x%x\n", mmio->vendor_id);
    printf("\thost_features 0x%x\n", mmio->host_features);
    printf("\tguest_page_size %u\n", mmio->guest_page_size);
    printf("\tqnum %u\n", mmio->queue_num);
    printf("\tqnum_max %u\n", mmio->queue_num_max);
    printf("\tqnum_align %u\n", mmio->queue_align);
    printf("\tqnum_pfn %u\n", mmio->queue_pfn);
    printf("\tstatus 0x%x\n", mmio->status);
}

void virtio_dump_desc(const struct vring_desc *desc)
{
    printf("vring descriptor %p\n", desc);
    printf("\taddr  0x%llx\n", desc->addr);
    printf("\tlen   0x%x\n", desc->len);
    printf("\tflags 0x%hhx\n", desc->flags);
    printf("\tnext  0x%hhx\n", desc->next);
}

static enum handler_return virtio_mmio_irq(void *arg)
{
    struct virtio_device *dev = (struct virtio_device *)arg;
    LTRACEF("dev %p, index %u\n", dev, dev->index);

    uint32_t irq_status = dev->mmio_config->interrupt_status;
    LTRACEF("status 0x%x\n", irq_status);

    enum handler_return ret = INT_NO_RESCHEDULE;
    if (irq_status & 0x1) { /* used ring update */
        // XXX is this safe?
        dev->mmio_config->interrupt_ack = 0x1;

        /* cycle through all the active rings */
        for (uint r = 0; r < MAX_VIRTIO_RINGS; r++) {
            if ((dev->active_rings_bitmap & (1<<r)) == 0)
                continue;

            struct vring *ring = &dev->ring[r];
            LTRACEF("ring %u: used flags 0x%hhx idx 0x%hhx last_used %u\n", r, ring->used->flags, ring->used->idx, ring->last_used);

            uint cur_idx = ring->used->idx;
            for (uint i = ring->last_used; i != (cur_idx & ring->num_mask); i = (i + 1) & ring->num_mask) {
                LTRACEF("looking at idx %u\n", i);

                // process chain
                struct vring_used_elem *used_elem = &ring->used->ring[i];
                LTRACEF("id %u, len %u\n", used_elem->id, used_elem->len);

                DEBUG_ASSERT(dev->irq_driver_callback);
                ret |= dev->irq_driver_callback(dev, r, used_elem);

                ring->last_used = (ring->last_used + 1) & ring->num_mask;
            }
        }
    }
    if (irq_status & 0x2) { /* config change */
        dev->mmio_config->interrupt_ack = 0x2;

        if (dev->config_change_callback) {
            ret |= dev->config_change_callback(dev);
        }
    }

    LTRACEF("exiting irq\n");

    return ret;
}

int virtio_mmio_detect(void *ptr, uint count, const uint irqs[])
{
    LTRACEF("ptr %p, count %u\n", ptr, count);

    DEBUG_ASSERT(ptr);
    DEBUG_ASSERT(irqs);
    DEBUG_ASSERT(!devices);

    /* allocate an array big enough to hold a list of devices */
    devices = calloc(count, sizeof(struct virtio_device));
    if (!devices)
        return ERR_NO_MEMORY;

    int found = 0;
    for (uint i = 0; i < count; i++) {
        volatile struct virtio_mmio_config *mmio = (struct virtio_mmio_config *)((uint8_t *)ptr + i * 0x200);
        struct virtio_device *dev = &devices[i];

        dev->index = i;
        dev->irq = irqs[i];

        mask_interrupt(irqs[i]);
        register_int_handler(irqs[i], &virtio_mmio_irq, (void *)dev);

        LTRACEF("looking at magic 0x%x version 0x%x did 0x%x vid 0x%x\n",
                mmio->magic, mmio->version, mmio->device_id, mmio->vendor_id);

        if (mmio->magic != VIRTIO_MMIO_MAGIC) {
            continue;
        }

#if LOCAL_TRACE
        if (mmio->device_id != 0) {
            dump_mmio_config(mmio);
        }
#endif

#if WITH_DEV_VIRTIO_BLOCK
        if (mmio->device_id == 2) { // block device
            LTRACEF("found block device\n");

            dev->mmio_config = mmio;
            dev->config_ptr = (void *)mmio->config;

            status_t err = virtio_block_init(dev, mmio->host_features);
            if (err >= 0) {
                // good device
                dev->valid = true;

                if (dev->irq_driver_callback)
                    unmask_interrupt(dev->irq);

                // XXX quick test code, remove
#if 0
                uint8_t buf[512];
                memset(buf, 0x99, sizeof(buf));
                virtio_block_read_write(dev, buf, 0, sizeof(buf), false);
                hexdump8_ex(buf, sizeof(buf), 0);

                buf[0]++;
                virtio_block_read_write(dev, buf, 0, sizeof(buf), true);

                virtio_block_read_write(dev, buf, 0, sizeof(buf), false);
                hexdump8_ex(buf, sizeof(buf), 0);
#endif
            }

        }
#endif // WITH_DEV_VIRTIO_BLOCK
#if WITH_DEV_VIRTIO_NET
        if (mmio->device_id == 1) { // network device
            LTRACEF("found net device\n");

            dev->mmio_config = mmio;
            dev->config_ptr = (void *)mmio->config;

            status_t err = virtio_net_init(dev, mmio->host_features);
            if (err >= 0) {
                // good device
                dev->valid = true;

                if (dev->irq_driver_callback)
                    unmask_interrupt(dev->irq);
            }
        }
#endif // WITH_DEV_VIRTIO_NET
#if WITH_DEV_VIRTIO_GPU
        if (mmio->device_id == 0x10) { // virtio-gpu
            LTRACEF("found gpu device\n");

            dev->mmio_config = mmio;
            dev->config_ptr = (void *)mmio->config;

            status_t err = virtio_gpu_init(dev, mmio->host_features);
            if (err >= 0) {
                // good device
                dev->valid = true;

                if (dev->irq_driver_callback)
                    unmask_interrupt(dev->irq);

                virtio_gpu_start(dev);
            }
        }
#endif // WITH_DEV_VIRTIO_GPU

        if (dev->valid)
            found++;
    }

    return found;
}

void virtio_free_desc(struct virtio_device *dev, uint ring_index, uint16_t desc_index)
{
    LTRACEF("dev %p ring %u index %u free_count %u\n", dev, ring_index, desc_index, dev->ring[ring_index].free_count);
    dev->ring[ring_index].desc[desc_index].next = dev->ring[ring_index].free_list;
    dev->ring[ring_index].free_list = desc_index;
    dev->ring[ring_index].free_count++;
}

uint16_t virtio_alloc_desc(struct virtio_device *dev, uint ring_index)
{
    if (dev->ring[ring_index].free_count == 0)
        return 0xffff;

    DEBUG_ASSERT(dev->ring[ring_index].free_list != 0xffff);

    uint16_t i = dev->ring[ring_index].free_list;
    struct vring_desc *desc = &dev->ring[ring_index].desc[i];
    dev->ring[ring_index].free_list = desc->next;

    dev->ring[ring_index].free_count--;

    return i;
}

struct vring_desc *virtio_alloc_desc_chain(struct virtio_device *dev, uint ring_index, size_t count, uint16_t *start_index)
{
    if (dev->ring[ring_index].free_count < count)
        return NULL;

    /* start popping entries off the chain */
    struct vring_desc *last = 0;
    uint16_t last_index = 0;
    while (count > 0) {
        uint16_t i = dev->ring[ring_index].free_list;
        struct vring_desc *desc = &dev->ring[ring_index].desc[i];

        dev->ring[ring_index].free_list = desc->next;
        dev->ring[ring_index].free_count--;

        if (last) {
            desc->flags = VRING_DESC_F_NEXT;
            desc->next = last_index;
        } else {
            // first one
            desc->flags = 0;
            desc->next = 0;
        }
        last = desc;
        last_index = i;
        count--;
    }

    if (start_index)
        *start_index = last_index;

    return last;
}

void virtio_submit_chain(struct virtio_device *dev, uint ring_index, uint16_t desc_index)
{
    LTRACEF("dev %p, ring %u, desc %u\n", dev, ring_index, desc_index);

    /* add the chain to the available list */
    struct vring_avail *avail = dev->ring[ring_index].avail;

    avail->ring[avail->idx & dev->ring[ring_index].num_mask] = desc_index;
    DSB;
    avail->idx++;

#if LOCAL_TRACE
    hexdump(avail, 16);
#endif
}

void virtio_kick(struct virtio_device *dev, uint ring_index)
{
    LTRACEF("dev %p, ring %u\n", dev, ring_index);

    dev->mmio_config->queue_notify = ring_index;
    DSB;
}

status_t virtio_alloc_ring(struct virtio_device *dev, uint index, uint16_t len)
{
    LTRACEF("dev %p, index %u, len %u\n", dev, index, len);

    DEBUG_ASSERT(dev);
    DEBUG_ASSERT(len > 0 && ispow2(len));
    DEBUG_ASSERT(index < MAX_VIRTIO_RINGS);

    if (len == 0 || !ispow2(len))
        return ERR_INVALID_ARGS;

    struct vring *ring = &dev->ring[index];

    /* allocate a ring */
    size_t size = vring_size(len, PAGE_SIZE);
    LTRACEF("need %zu bytes\n", size);

#if WITH_KERNEL_VM
    void *vptr;
    status_t err = vmm_alloc_contiguous(vmm_get_kernel_aspace(), "virtio_ring", size, &vptr, 0, 0, ARCH_MMU_FLAG_UNCACHED_DEVICE);
    if (err < 0)
        return ERR_NO_MEMORY;

    LTRACEF("allocated virtio_ring at va %p\n", vptr);

    /* compute the physical address */
    paddr_t pa;
    pa = vaddr_to_paddr(vptr);
    if (pa == 0) {
        return ERR_NO_MEMORY;
    }

    LTRACEF("virtio_ring at pa 0x%lx\n", pa);
#else
    void *vptr = memalign(PAGE_SIZE, size);
    if (!vptr)
        return ERR_NO_MEMORY;

    LTRACEF("ptr %p\n", vptr);
    memset(vptr, 0, size);

    /* compute the physical address */
    paddr_t pa = (paddr_t)vptr;
#endif

    /* initialize the ring */
    vring_init(ring, len, vptr, PAGE_SIZE);
    dev->ring[index].free_list = 0xffff;
    dev->ring[index].free_count = 0;

    /* add all the descriptors to the free list */
    for (uint i = 0; i < len; i++) {
        virtio_free_desc(dev, index, i);
    }

    /* register the ring with the device */
    DEBUG_ASSERT(dev->mmio_config);
    dev->mmio_config->guest_page_size = PAGE_SIZE;
    dev->mmio_config->queue_sel = index;
    dev->mmio_config->queue_num = len;
    dev->mmio_config->queue_align = PAGE_SIZE;
    dev->mmio_config->queue_pfn = pa / PAGE_SIZE;

    /* mark the ring active */
    dev->active_rings_bitmap |= (1 << index);

    return NO_ERROR;
}

void virtio_reset_device(struct virtio_device *dev)
{
    dev->mmio_config->status = 0;
}

void virtio_status_acknowledge_driver(struct virtio_device *dev)
{
    dev->mmio_config->status |= VIRTIO_STATUS_ACKNOWLEDGE | VIRTIO_STATUS_DRIVER;
}

void virtio_status_driver_ok(struct virtio_device *dev)
{
    dev->mmio_config->status |= VIRTIO_STATUS_DRIVER_OK;
}

void virtio_init(uint level)
{
}

LK_INIT_HOOK(virtio, &virtio_init, LK_INIT_LEVEL_THREADING);

