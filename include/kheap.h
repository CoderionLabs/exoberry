#ifndef KHEAP_H
#define KHEAP_H

#include "sys.h"
#include "mm.h"


typedef struct _KHEAPBLOCKBM {
	struct _KHEAPBLOCKBM * next;	 // Pointer to next block
	uint32_t			   size;	 // Size of memory in bytes
	uint32_t			   used;	 // # of blocks used
	uint32_t			   bsize;	 // Block size
	uint32_t			   lfb;
} KHEAPBLOCKBM;

// Header for kernel heap
typedef struct _KHEAPBM {
	KHEAPBLOCKBM * fblock;
} KHEAPBM;

void k_heapBMInit(KHEAPBM * heap);

int k_heapBMAddBlock(KHEAPBM * heap, uintptr_t addr, uint32_t size, uint32_t bsize);

static uint8_t k_heapBMGetNID(uint8_t a, uint8_t b);

void * k_heapBMAlloc(KHEAPBM * heap, uint32_t size);

void k_heapBMFree(KHEAPBM * heap, void * ptr);

#endif
