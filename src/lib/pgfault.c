// Set the page fault handler that will 
// be called in pfentry.S

#include "lib/lib.h"

int (*pgfault_handler)(unsigned long addr, unsigned long esr);


void set_pgfault_handler(int (*handler)(unsigned long addr, unsigned long esr)){
    
    pgfault_handler = handler;
}
