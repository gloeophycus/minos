.intel_syntax	noprefix
.globl	_start
.code16

#.org	0xC200

.equ	MAIN, 0x00280000
.equ	DISK_CACHE, 0x00100000
.equ	REAL_MODE_DISK_CACHE, 0x00008000
.equ	SECTORS, 0x0FF0
.equ	LEDS, 0x0FF1
.equ	VMODE, 0x0FF2
.equ	SCREEN_X, 0x0FF4
.equ	SCREEN_Y, 0x0FF6
.equ	VRAM, 0x0FF8

_start:
	mov	ah, 0x00
	mov	al, 0x13	# vga graphics 320x200x8 bit color
	int	0x10

	mov	byte ptr [VMODE], 8
	mov	word ptr [SCREEN_X], 320
	mov	word ptr [SCREEN_Y], 200
	mov	dword ptr [VRAM], 0x000A0000

# get keyboard led state
	mov	ah, 0x02
	int	0x16
	mov	[LEDS], al

# enable a20 gate via bios
	mov	ax, 0x2401
	int	0x15
	jnc	a20_gate_enabled

# enable a20 gate via system control port
	in	al, 0x92
	or	al, 0x02
	and	al, 0xFE
	out	0x92, al

a20_gate_enabled:

# disable pic interrupts
	mov	al, 0xFF
	out	0x21, al
	nop
	out	0xA1, al

# disable cpu interrupts
	cli

# transit to protect mode
	lgdt	[gdtr]
	mov	eax, cr0
	or	eax, 0x00000001	# PE = 1
	and	eax, 0x7FFFFFFF	# PG = 0
	mov	cr0, eax
	jmp	protect_mode

protect_mode:
	mov	ax, 0x08	# data descriptor offset
	mov	ds, ax
	mov	es, ax
	mov	fs, ax
	mov	gs, ax
	mov	ss, ax

	mov	esi, offset main
	mov	edi, MAIN
	mov	ecx, 512 * 1024 / 4
	call	memcpy

	mov	esi, 0x7C00
	mov	edi, DISK_CACHE
	mov	ecx, 512 / 4
	call	memcpy

	mov	esi, REAL_MODE_DISK_CACHE + 512
	mov	edi, DISK_CACHE + 512
	mov	ecx, 0
	mov	cl, [SECTORS]
	imul	ecx, 512 * 18 * 2 / 4
	sub	ecx, 512 / 4
	call	memcpy

	mov	ebx, MAIN
	mov	ecx, [ebx + 16]
	add	ecx, 3
	shr	ecx, 2
	jz	skip
	mov	esi, [ebx + 20]
	add	esi, ebx
	mov	edi, [ebx + 12]
	call	memcpy
skip:
	mov	esp, [ebx + 12]
	jmp	0x10:0x0000001B

memcpy:
	mov	eax, [esi]
	add	esi, 4
	mov	[edi], eax
	add	edi, 4
	sub	ecx, 1
	jnz	memcpy
	ret

	.align	8

	.word	0		# gdtr memory alignment (word + double word)
gdtr:
	.word	8 * 3 - 1	# gdt size
	.long	gdt		# gdt address

gdt:
null_descriptor:
	.word	0x0000		# limit
	.word	0x0000		# base low
	.byte	0x00		# base mid
	.byte	0x00		# P, DPL, S, type
	.byte	0x00		# G, D/B, L, AVL, limit
	.byte	0x00		# base high

data_descriptor:
	.word	0xFFFF		# limit
	.word	0x0000		# base low
	.byte	0x00		# base mid
	.byte	0x92		# P = 1, DPL = 0, S = 1, type = 0x02 (read/write)
	.byte	0xCF		# G = 1, D/B = 1, L = 0, AVL = 0, limit
	.byte	0x00		# base high

# segment for main: 0x00280000
code_descriptor:
	.word	0xFFFF		# limit
	.word	0x0000		# base low
	.byte	0x28		# base mid
	.byte	0x9A		# P = 1, DPL = 0, S = 1, type = 0x0A (read/write)
	.byte	0x47		# G = 0, D/B = 1, L = 0, AVL = 0, limit
	.byte	0x00		# base high

main:
