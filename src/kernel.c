#include <stddef.h>
#include <stdint.h>

#include "printf.h"
#include "utils.h"
#include "timer.h"
#include "irq.h"
#include "lib/lib.h"
#include "lib/fork.h"
#include "sched.h"
#include "mini_uart.h"
#include "liballoc.h"
#include "sys.h"


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


void kernel_main()
{
	uart_init();
	init_printf(NULL, putc);
	irq_vector_init();
	timer_init();
	enable_interrupt_controller();
	enable_irq();

    printf("Welcome to Exoberry OS!");

    printf("Testing Memory Allocator");

    char* x = (char*) malloc(sizeof(char) * 9);

    for(int i = 0; i < 9; i++){
        x[i] = "A";
    }

    printf("%s", x);


	int res = copy_process(PF_KTHREAD, (unsigned long)&kernel_process, 0);

	if (res < 0) {
		printf("error while starting kernel process");
		return;
	}

	while (1) {
		schedule();
	}
}
