#include "mm.h"
#include "arm/mmu.h"

static unsigned short mem_map[PAGING_PAGES] = {
	0,
};

unsigned long allocate_kernel_page()
{
	unsigned long page = get_free_page();
	if (page == 0) {
		return 0;
	}
	return page + VA_START;
}

// Trash function to allocate multiple kernel pages
// TODO: check if this actually works
unsigned long allocate_kernel_pages(int num_pages){
    int rez = 0;
    for(int i = 0; i < num_pages; i++){
        if(i == 0){
            rez = allocate_kernel_page();
        }else{
            allocate_kernel_page();
        }
    }
    return rez;
}

void free_kernel_pages(unsigned long startva, int num_pages){
    
    for(int i = 0; i < num_pages; i++){
        free_page(startva + (PAGE_SIZE * i));
    }
}


unsigned long allocate_user_page(struct task_struct * task, unsigned long va)
{
	unsigned long page = get_free_page();
	if (page == 0) {
		return 0;
	}
	map_page(task, va, page);
	return page + VA_START;
}

unsigned long get_free_page()
{
	for (int i = 0; i < PAGING_PAGES; i++) {
		if (mem_map[i] == 0) {
			mem_map[i]		   = 1;
			unsigned long page = LOW_MEMORY + i * PAGE_SIZE;
			memzero(page + VA_START, PAGE_SIZE);
			return page;
		}
	}
	return 0;
}

void free_page(unsigned long p)
{
	mem_map[(p - LOW_MEMORY) / PAGE_SIZE] = 0;
}

void map_table_entry(unsigned long * pte, unsigned long va, unsigned long pa)
{
	unsigned long index = va >> PAGE_SHIFT;
	index				= index & (PTRS_PER_TABLE - 1);
	unsigned long entry = pa | MMU_PTE_FLAGS;
	pte[index]			= entry;
}

unsigned long map_table(unsigned long * table, unsigned long shift, unsigned long va, int * new_table)
{
	unsigned long index = va >> shift;
	index				= index & (PTRS_PER_TABLE - 1);
	if (!table[index]) {
		*new_table					   = 1;
		unsigned long next_level_table = get_free_page();
		unsigned long entry			   = next_level_table | MM_TYPE_PAGE_TABLE;
		table[index]				   = entry;
		return next_level_table;
	} else {
		*new_table = 0;
	}
	return table[index] & PAGE_MASK;
}

void map_page(struct task_struct * task, unsigned long va, unsigned long page)
{
	unsigned long pgd;
	if (!task->mm.pgd) {
		task->mm.pgd										 = get_free_page();
		task->mm.kernel_pages[++task->mm.kernel_pages_count] = task->mm.pgd;
	}
	pgd = task->mm.pgd;
	int			  new_table;
	unsigned long pud = map_table((unsigned long *)(pgd + VA_START), PGD_SHIFT, va, &new_table);
	if (new_table) {
		task->mm.kernel_pages[++task->mm.kernel_pages_count] = pud;
	}
	unsigned long pmd = map_table((unsigned long *)(pud + VA_START), PUD_SHIFT, va, &new_table);
	if (new_table) {
		task->mm.kernel_pages[++task->mm.kernel_pages_count] = pmd;
	}
	unsigned long pte = map_table((unsigned long *)(pmd + VA_START), PMD_SHIFT, va, &new_table);
	if (new_table) {
		task->mm.kernel_pages[++task->mm.kernel_pages_count] = pte;
	}
	map_table_entry((unsigned long *)(pte + VA_START), va, page);
	struct user_page p								 = {page, va};
	task->mm.user_pages[task->mm.user_pages_count++] = p;
}

int copy_virt_memory(struct task_struct * dst)
{
	struct task_struct * src = current;
	for (int i = 0; i < src->mm.user_pages_count; i++) {
		unsigned long kernel_va = allocate_user_page(dst, src->mm.user_pages[i].virt_addr);
		if (kernel_va == 0) {
			return -1;
		}
		memcpy(kernel_va, src->mm.user_pages[i].virt_addr, PAGE_SIZE);
	}
	return 0;
}
