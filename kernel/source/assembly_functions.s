.intel_syntax	noprefix
.global		hlt, cli, sti, sti_hlt
.global		in_8bit, in_16bit, in_32bit
.global		out_8bit, out_16bit, out_32bit
.global		read_eflags, write_eflags
.global		read_cr0, write_cr0
.global		load_gdtr, load_idtr
.global		_keyboard_interrupt_handler, _mouse_interrupt_handler
.extern 	keyboard_interrupt_handler, mouse_interrupt_handler
hlt:
	hlt
	ret

cli:
	cli
	ret

sti:
	sti
	ret

sti_hlt:
	sti
	hlt
	ret

in_8bit:
	mov	edx, [esp + 4]
	mov	eax, 0
	in	al, dx
	ret

in_16bit:
	mov	edx, [esp + 4]
	mov	eax, 0
	in	ax, dx
	ret

in_32bit:
	mov	edx, [esp + 4]
	in	eax, dx
	ret

out_8bit:
	mov	edx, [esp + 4]
	mov	eax, [esp + 8]
	out	dx, al
	ret

out_16bit:
	mov	edx, [esp + 4]
	mov	eax, [esp + 8]
	out	dx, ax
	ret

out_32bit:
	mov	edx, [esp + 4]
	mov	eax, [esp + 8]
	out	dx, eax
	ret

read_eflags:
	pushfd
	pop	eax
	ret

write_eflags:
	mov	eax, [esp + 4]
	push	eax
	popfd
	ret	
	
read_cr0:
	mov	eax, cr0
	ret

write_cr0:
	mov	eax, [esp + 4]
	mov	cr0, eax
	ret

load_gdtr:
	mov	ax, [esp + 4]
	mov	[esp + 6], ax
	lgdt	[esp + 6]
	ret

load_idtr:
	mov	ax, [esp + 4]
	mov	[esp + 6], ax
	lidt	[esp + 6]
	ret

_keyboard_interrupt_handler:
	push	es
	push	ds
	pushad
	mov	eax, esp
	push	eax
	mov	ax, ss
	mov	ds, ax
	mov	es, ax
	call	keyboard_interrupt_handler
	pop	eax
	popad
	pop	ds
	pop	es
	iretd

_mouse_interrupt_handler:
	push	es
	push	ds
	pushad
	mov	eax, esp
	push	eax
	mov	ax, ss
	mov	ds, ax
	mov	es, ax
	call	mouse_interrupt_handler
	pop	eax
	popad
	pop	ds
	pop	es
	iretd
