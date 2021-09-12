#include <stddef.h>
#include <stdint.h>

#include "printf.h"
#include "utils.h"
#include "timer.h"
#include "irq.h"
#include "mm.h"
#include "lib/lib.h"
#include "lib/fork.h"
#include "sched.h"
#include "mini_uart.h"
#include "sys.h"
#include "kheap.h"

void cool_putc(void * p, char c)
{
	if (c == '\n') {
		uart_send('\r');
	}

	uart_send(c);
}


void kernel_process()
{
	printf("Library OS process started. EL %d\r\n", get_el());
	unsigned long begin	  = (unsigned long)&lib_begin;
	unsigned long end	  = (unsigned long)&lib_end;
	unsigned long process = (unsigned long)&libmain;
	int			  err	  = move_to_user_mode(begin, end - begin, process - begin);
	if (err < 0) {
		printf("Error while moving process to user mode\n\r");
	}
}

void test_heap()
{
    printf("TESTING HEAP\n");
	KHEAPBM kheap;
	char *	ptr;

	k_heapBMInit(&kheap); /* initialize the heap */
	printf("INIT PASSED\n");

	k_heapBMAddBlock(&kheap, KHEAP_START, KHEAP_SIZE, 16);
	printf("ADDED BLOCK PASSED\n");

	ptr = (char *)k_heapBMAlloc(&kheap, 256); /* allocate 256 bytes (malloc) */
	printf("ALLOCATION PASSED\n");

    char* cool = "COOL";
    memcpy(ptr,  cool, 4);
    printf("MEMORY WRITE PASSED\n");

	printf("%s\n", ptr);
	k_heapBMFree(&kheap, ptr);
	printf("FREE PASSED\n");
}

void kernel_main()
{
	uart_init();
	init_printf(NULL, cool_putc);
	irq_vector_init();
	timer_init();
	enable_interrupt_controller();
	enable_irq();
	kheap_init();

	printf("Welcome to Exoberry OS!\n");

	test_heap();
	int res = copy_process(PF_KTHREAD, (unsigned long)&kernel_process, 0);

	if (res < 0) {
		printf("error while starting kernel process");
		return;
	}

	while (1) {
		schedule();
	}
}
