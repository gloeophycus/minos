OUTPUT_FORMAT("binary");

SECTIONS
{
	.head 0x0 :
	{
		LONG(128 * 1024)		/* 0x00: stack + .data + heap size */
		LONG(0x206E696D)		/* 0x04: "min " */
		LONG(0)					/* 0x08: "memory map area size */
		LONG(0x0400)			/* 0x0C: stack initial value & .data destination */
		LONG(SIZEOF(.data))		/* 0x10: .data size */
		LONG(LOADADDR(.data))	/* 0x14: .data initial value file offset */
		LONG(0xE9000000)		/* 0x18: jump pattern (x86 jmp) */
		LONG(_main - 0x20)		/* 0x1C: entry point (main - 0x20) */
		LONG(0)					/* 0x20: heap start address */
	}

	.text : { *(.text) }

	.data 0x0400 : AT ( ADDR(.text) + SIZEOF(.text) )
	{
		*(.data)
		*(.rodata*)
		*(.bss)
	}

	.eh_frame : { *(.eh_frame) }
}
