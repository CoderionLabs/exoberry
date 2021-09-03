#include "spin_lock.h"
#include "mm.h"    // PAGE_SIZE


//TODO: Implment mutex locks
spinlock_t lock;

int liballoc_lock()
{
    spin_lock(&lock);
    return 0;
}

int liballoc_unlock()
{
    spin_unlock(&lock);
	return 0;
}

void* liballoc_alloc( int pages )
{
		
	char *p2 = (char*)allocate_kernel_pages(pages);

    if(p2 == 0){
        // NO MEMEORY LEFT
    }

	return p2;
}

int liballoc_free(void* ptr, int pages)
{
    // TODO: Handle memory errors
    free_kernel_pages(ptr, pages);
    return 0;
}
