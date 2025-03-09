.intel_syntax	noprefix
.global		hlt, cli, sti, sti_hlt
.global		in_8bit, in_16bit, in_32bit
.global		out_8bit, out_16bit, out_32bit
.global		load_eflags, store_eflags

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

load_eflags:
	pushfd
	pop	eax
	ret

store_eflags:
	mov	eax, [esp + 4]
	push	eax
	popfd
	ret	
	