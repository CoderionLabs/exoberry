/*
    2014 Leonard Kevin McGuire Jr (www.kmcg3413.net) (kmcg3413@gmail.com)
    2016 Clément Gallet (provided bug fixes)
    2021 Friedrich Doku
*/

#include "kheap.h"
#include "printf.h"

void k_heapBMInit(KHEAPBM * heap)
{
	heap->fblock = 0;
}

int k_heapBMAddBlock(KHEAPBM * heap, uintptr_t addr, uint32_t size, uint32_t bsize)
{
	KHEAPBLOCKBM * b;		// Our new Block
	uint32_t	   bcnt;	// Number of blocks
	uint32_t	   x;
	uint8_t *	   bm;	  // Bitmap

	b		 = (KHEAPBLOCKBM *)addr;		   // Align the block to this address
	b->size	 = size - sizeof(KHEAPBLOCKBM);	   // Set the size of the block
	b->bsize = bsize;						   // Set our block size

	b->next		 = heap->fblock;	// Make the previous first block our next one
	heap->fblock = b;				// Set the first block to this block

	bcnt = b->size / b->bsize;	  // Number of blocks
	bm	 = (uint8_t *)&b[1];	  // Start our bitmap after block header

	/* clear bitmap */
	for (x = 0; x < bcnt; ++x) {
		bm[x] = 0;
	}

	/* Use some of the blocks for our bitmap */
	bcnt = (bcnt / bsize) * bsize < bcnt ? bcnt / bsize + 1 : bcnt / bsize;
	for (x = 0; x < bcnt; ++x) {
		bm[x] = 5;
	}

	b->lfb = bcnt - 1;	  // The location of our last free block

	b->used = bcnt;	   // Number of blocks used

	return 1;
}

static uint8_t k_heapBMGetNID(uint8_t a, uint8_t b)
{
	uint8_t c;
	for (c = a + 1; c == b || c == 0; ++c);
	return c;
}

void * k_heapBMAlloc(KHEAPBM * heap, uint32_t size)
{
	KHEAPBLOCKBM * b;
	uint8_t *	   bm;
	uint32_t	   bcnt;
	uint32_t	   x, y, z;
	uint32_t	   bneed;
	uint8_t		   nid;

	/* iterate blocks */
	for (b = heap->fblock; b; b = b->next) {
		/* check if block has enough room */
		if (b->size - (b->used * b->bsize) >= size) {
            printf("WERE IN HERE b->size=%d b->used=%d b->bsize=%d\n", b->size, b->used, b->bsize);
			/* number of blocks */
			bcnt = b->size / b->bsize;
			/* number of blocks needed */
			bneed = (size / b->bsize) * b->bsize < size ? size / b->bsize + 1 : size / b->bsize;
			/* Set the bitmap */
			bm = (uint8_t *)&b[1];


            printf("DATA b->lfb=%d bcnt=%d\n", b->lfb, bcnt);
            if((b->lfb + 1) >= bcnt){
                x = 0;
                //printf("LFB IS BIGGER\n");
            }else{
                x = b->lfb +1;
                //printf("LFB IS SMALLER\n");
            }
			
            for (; x < bcnt; ++x) {
                //printf("LOOPING\n");
				/* just wrap around */
				if (x >= bcnt) {
					x = 0;
				}

				if (bm[x] == 0) {
                    //printf("WERE IN HERE 1\n");
					/* count free blocks */
					for (y = 0; bm[x + y] == 0 && y < bneed && (x + y) < bcnt; ++y);

					/* we have enough, now allocate them */
					if (y == bneed) {
                        //printf("WERE IN HERE 2\n");
						/* find ID that does not match left or right */
						nid = k_heapBMGetNID(bm[x - 1], bm[x + y]);

						/* allocate by setting id */
						for (z = 0; z < y; ++z) {
							bm[x + z] = nid;
						}

						/* optimization */
						b->lfb = (x + bneed) - 2;

						/* count used blocks NOT bytes */
						b->used += y;
                        
                        //printf("PASSED\n");
						return (void *)(x * b->bsize + (uintptr_t)&b[1]);
					}

					/* x will be incremented by one ONCE more in our FOR loop */
					x += (y - 1);
					continue;
				}
			}
		}
	}

    printf("MEMORY ALLOCATION FAILED\n");
	return 0;
}

void k_heapBMFree(KHEAPBM * heap, void * ptr)
{
	KHEAPBLOCKBM * b;
	uintptr_t	   ptroff;
	uint32_t	   bi, x;
	uint8_t *	   bm;
	uint8_t		   id;
	uint32_t	   max;

	for (b = heap->fblock; b; b = b->next) {
		if ((uintptr_t)ptr > (uintptr_t)b && (uintptr_t)ptr < (uintptr_t)b + sizeof(KHEAPBLOCKBM) + b->size) {
			/* found block */
			ptroff = (uintptr_t)ptr - (uintptr_t)&b[1]; /* get offset to get block */
			/* block offset in BM */
			bi = ptroff / b->bsize;
			/* .. */
			bm = (uint8_t *)&b[1];
			/* clear allocation */
			id = bm[bi];
			/* oddly.. GCC did not optimize this */
			max = b->size / b->bsize;
			for (x = bi; bm[x] == id && x < max; ++x) {
				bm[x] = 0;
			}
			/* update free block count */
			b->used -= x - bi;
			return;
		}
	}

	/* this error needs to be raised or reported somehow */
	return;
}
