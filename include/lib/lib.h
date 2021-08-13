#ifndef LIB_H
#define LIB_H

extern unsigned long lib_begin;
extern unsigned long lib_end;

void umain();
void libmain();

void set_pgfault_handler(int (*handler)(unsigned long addr, unsigned long esr));

#endif
