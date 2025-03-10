#include "assembly_functions.h"
#include "entrypoint.h"
#include "graphics.h"
#include "interrupts.h"

void initialize_pic(void)
{
	out_8bit(PIC0_IMR, 0xFF); // disable all interrupts
	out_8bit(PIC1_IMR, 0xFF); // disable all interrupts
	out_8bit(PIC0_ICW1, 0x11); // edge trigger mode
	out_8bit(PIC0_ICW2, 0x20); // irq0: int 0x20 ~ irq7: int 0x27
	out_8bit(PIC0_ICW3, 1 << 2); // irq2: pic1
	out_8bit(PIC0_ICW4, 0x01); // nonbuffer mode
	out_8bit(PIC1_ICW1, 0x11); // edge trigger mode
	out_8bit(PIC1_ICW2, 0x28); // irq8: int 0x28 ~ irq15: int 0x2F
	out_8bit(PIC1_ICW3, 2); // irq2: pic1
	out_8bit(PIC1_ICW4, 0x01); // nonbuffer mode
	out_8bit(PIC0_IMR, 0xFB); // disable all interrupts except pic1
	out_8bit(PIC1_IMR, 0xFF); // disable all interrupts
}

void keyboard_interrupt_handler(__attribute__((unused))int *esp)
{
	SystemInfo *system_info = (SystemInfo*)SYSTEM_INFO_ADDRESS;
	draw_rectangle(system_info->screen_x, BLACK, (Point){0, 0}, (Point){32 * 8 - 1, 15}, system_info->vram);
	print_string(system_info->screen_x, WHITE, (Point){0, 0}, "INT 21 (IRQ-1): PS/2 keyboard", system_info->vram);

	while (1)
	{
		hlt();
	}
}

void mouse_interrupt_handler(__attribute__((unused))int *esp)
{
	SystemInfo *system_info = (SystemInfo*)SYSTEM_INFO_ADDRESS;
	draw_rectangle(system_info->screen_x, BLACK, (Point){0, 0}, (Point){32 * 8 - 1, 15}, system_info->vram);
	print_string(system_info->screen_x, WHITE, (Point){0, 0}, "INT 2C (IRQ-12): PS/2 mouse", system_info->vram);

	while (1)
	{
		hlt();
	}
}