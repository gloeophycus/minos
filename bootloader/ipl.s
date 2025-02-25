.intel_syntax	noprefix
.global _start
.code16

.equ	SECTORS, 10

 _start:
	jmp	entry
	
.byte	0x90
.ascii	"MIN-IPL "	# boot sector name (8 bytes)
.word	512		# sector size
.byte	1		# cluster size
.word	1		# fat starting point
.byte	2		# fat number
.word	224		# root directory size
.word	2880		# drive size
.byte	0xF0		# media type
.word	9		# fat length
.word	18		# track number
.word	2		# head number
.long	0		# partition
.long	2880		# drive size
.byte	0, 0, 0x29
.long	0xFFFFFFFF	# volume serial number
.ascii	"MINOS      "	# disk name (11 bytes)
.ascii	"FAT12   "	# format name (8 bytes)
.space	18

entry:
	mov	ax, 0
	mov	ds, ax
	mov	ss, ax
	mov	sp, 0x7C00

# reset disk
	mov	ax, 0x00	# reset
	mov	dl, 0x00	# drive number
	int	0x13
	jc	disk_error

# read disk
	mov	ah, 0x02	# read
	mov	al, 0x01	# sector number
	mov	ch, 0x00	# track
	mov	cl, 0x02	# sector
	mov	dh, 0x00	# head
	mov	dl, 0x00	# drive number
	mov	si, 0x0820
	mov	es, si		# memory
	mov	bx, 0		# memory offset
disk_loop:
	mov	ah, 0x02
	int	0x13
	jc	disk_error
	add	si, 0x0020
	mov	es, si
	add	cl, 1
	cmp	cl, 18
	jbe	disk_loop
	mov	cl, 1
	add	dh, 1
	cmp	dh, 2
	jb	disk_loop
	mov	dh, 0
	add	ch, 1
	cmp	ch, SECTORS
	jb	disk_loop

	mov	[0x0FF0], ch
	jmp	0xC200

disk_error:
	mov	ax, 0
	mov	es, ax
	mov	ah, 0x0E	# character
	mov	bx, 0x0F	# color
	mov	si, offset message
message_loop:
	mov	al, [si]
 	int	0x10
 	add	si, 1
	cmpb	[si], 0
	jne	message_loop

fin:
	hlt
	jmp	fin

message:
	.ascii	"Disk error"
	.byte	0x00

.org 510
	.byte	0x55, 0xAA
