#include "assembly_functions.h"
#include "descriptors.h"

void set_segment_descriptor(unsigned int limit, int base, int access_right, SegmentDescriptor *segment_descriptor)
{
	if (limit > 0xFFFFF)
	{
		access_right |= 0x8000; // G = 1
		limit /= 0x1000;
	}

	segment_descriptor->limit_low = limit & 0xFFFF;
	segment_descriptor->limit_high = ((limit >> 16) & 0x0F) | ((access_right >> 8) & 0xF0);
	segment_descriptor->base_low = base & 0xFFFF;
	segment_descriptor->base_mid = (base >> 16) & 0xFF;
	segment_descriptor->base_high = (base >> 24) & 0xFF;
	segment_descriptor->access_right = access_right & 0xFF;
}

void set_gate_descriptor(int offset, int selector, int access_right, GateDescriptor *gate_descriptor)
{
	gate_descriptor->offset_low = offset & 0xFFFF;
	gate_descriptor->offset_high = (offset >> 16) & 0xFFFF;
	gate_descriptor->selector = selector;
	gate_descriptor->access_right = access_right & 0xFF;
	gate_descriptor->count = (access_right >> 8) & 0xFF;
}

void initialize_gdt(void)
{
	const int GDT_ADDRESS = 0x00270000;
	const int GDT_LIMIT = 0x0000FFFF;
	SegmentDescriptor *gdt = (SegmentDescriptor*)GDT_ADDRESS;
	for (int i = 0; i < GDT_LIMIT / 8; i++)
	{
		set_segment_descriptor(0, 0, 0, gdt + i);
	}

	const int KERNEL_ADDRESS = 0x00280000;
	const int KERNEL_LIMIT = 0x0007FFFF;
	const int DATA_RW_ACCESS_RIGHT = 0x4092; // G = 0, D = 1, L = 0, AVL = 0, P = 1, DPL = 0, S = 1, type = 0x02 (data segment read/write)
	const int CODE_ER_ACCESS_RIGHT = 0x409A; // G = 0, D = 1, L = 0, AVL = 0, P = 1, DPL = 0, S = 1, type = 0x0A (code segment execute/read)
	set_segment_descriptor(0xFFFFFFFF, 0x00000000, DATA_RW_ACCESS_RIGHT, gdt + 1);
	set_segment_descriptor(KERNEL_LIMIT, KERNEL_ADDRESS, CODE_ER_ACCESS_RIGHT, gdt + 2);
	load_gdtr(GDT_LIMIT, GDT_ADDRESS);
}

void initialize_idt(void)
{
	const int IDT_ADDRESS = 0x0026F800;
	const int IDT_LIMIT = 0x000007FF;
	GateDescriptor *idt = (GateDescriptor*)IDT_ADDRESS;
	for (int i = 0; i < IDT_LIMIT / 8; i++)
	{
		set_gate_descriptor(0, 0, 0, idt + i);
	}
	load_idtr(IDT_LIMIT, IDT_ADDRESS);

	const int INTERRUPT_GATE_ACCESS_RIGHT = 0x008E;
	set_gate_descriptor((int)_keyboard_interrupt_handler, 2 << 3, INTERRUPT_GATE_ACCESS_RIGHT, idt + 0x21);
	set_gate_descriptor((int)_mouse_interrupt_handler, 2 << 3, INTERRUPT_GATE_ACCESS_RIGHT, idt + 0x2C);
}