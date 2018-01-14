#include <inc/mmu.h>
#include <inc/memlayout.h>

pte_t entry_pgtable[NPTENTRIES];

// The entry.S page directory maps the first 4MB of physical memory
// starting at virtual address KERNBASE (that is, it maps virtual
// addresses [KERNBASE, KERNBASE+4MB) to physical addresses [0, 4MB)).
// We choose 4MB because that's how much we can map with one page
// table and it's enough to get us through early boot.  We also map
// virtual addresses [0, 4MB) to physical addresses [0, 4MB); this
// region is critical for a few instructions in entry.S and then we
// never use it again.
//
// Page directories (and page tables), must start on a page boundary,
// hence the "__aligned__" attribute.  Also, because of restrictions
// related to linking and static initializers, we use "x + PTE_P"
// here, rather than the more standard "x | PTE_P".  Everywhere else
// you should use "|" to combine flags.

#define LVL0(i)  ((i) * PGSIZE) | PTE_P | PTE_W
#define LVL1(i)  LVL0(i), LVL0((i) + 1)
#define LVL2(i)  LVL1(i), LVL1((i) + 2)
#define LVL3(i)  LVL2(i), LVL2((i) + 4)
#define LVL4(i)  LVL3(i), LVL3((i) + 8)
#define LVL5(i)  LVL4(i), LVL4((i) + 16)
#define LVL6(i)  LVL5(i), LVL5((i) + 32)
#define LVL7(i)  LVL6(i), LVL6((i) + 64)
#define LVL8(i)  LVL7(i), LVL7((i) + 128)
#define LVL9(i)  LVL8(i), LVL8((i) + 256)
#define LVL10(i) LVL9(i), LVL9((i) + 512)

__attribute__((__aligned__(PGSIZE)))
pde_t entry_pgdir[NPDENTRIES] = {
	// Map VA's [0, 4MB) to PA's [0, 4MB)
	[0]
		= ((uintptr_t)entry_pgtable - KERNBASE) + PTE_P,
	// Map VA's [KERNBASE, KERNBASE+4MB) to PA's [0, 4MB)
	[KERNBASE >> PDXSHIFT]
		= ((uintptr_t)entry_pgtable - KERNBASE) + PTE_P + PTE_W
};

// Entry 0 of the page table maps to physical page 0, entry 1 to
// physical page 1, etc.We do this using the hand-written, statically-initialized page directory and page table in kern/entrypgdir.c.
__attribute__((__aligned__(PGSIZE)))
pte_t entry_pgtable[NPTENTRIES] = {
    LVL10(0)
};
