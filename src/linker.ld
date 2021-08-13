SECTIONS
{
	. = 0xffff000000000000;
	.text.boot : { *(.text.boot) }
	. = ALIGN(0x00001000);
	lib_begin = .;
	.text.lib : { build/lib* (.text) }
	.rodata.lib : { build/lib* (.rodata) }
	.data.lib : { build/lib* (.data) }
	.bss.lib : { build/lib* (.bss) }
	lib_end = .;
	.text :  { *(.text) }
	.rodata : { *(.rodata) }
	.data : { *(.data) }
	. = ALIGN(0x8);
	bss_begin = .;
	.bss : { *(.bss*) } 
	bss_end = .;
	. = ALIGN(0x00001000);
	pg_dir = .;
	.data.pgd : { . += (3 * (1 << 12)); }
}

