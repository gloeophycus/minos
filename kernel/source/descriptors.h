#ifndef DESCRIPOTRS_H
#define DESCRIPTORS_H

#define G_BIT 1 << 15
#define GDT_ADDRESS 0x00270000
#define GDT_LIMIT 0x0000FFFF
#define KERNEL_ADDRESS 0x00280000
#define KERNEL_LIMIT 0x0007FFFF
#define IDT_ADDRESS 0x0026F800
#define IDT_LIMIT 0x000007FF

typedef struct
{
	short limit_low;
	short base_low;
	char base_mid;
	char access_right; // P, DPL, S, type
	char limit_high; // G, D/B, L, AVL, limit
	char base_high;
} SegmentDescriptor;

typedef struct
{
	short offset_low;
	short selector;
	char count;
	char access_right;
	short offset_high;
} GateDescriptor;

void set_segment_descriptor(unsigned int limit, int base, int access_right, SegmentDescriptor *segment_descriptor);
void set_gate_descriptor(int offset, int selector, int access_right, GateDescriptor *gate_descriptor);
void initialize_gdt(void);
void initialize_idt(void);

#endif