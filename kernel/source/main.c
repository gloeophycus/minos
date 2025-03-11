#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "descriptors.h"
#include "entrypoint.h"
#include "graphics.h"
#include "interrupts.h"
#include "queue.h"

extern Queue keyboard_queue;

void _main(void)
{
	initialize_gdt();
	initialize_idt();
	initialize_pic();
	sti(); // enable cpu interrupts

	SystemInfo *system_info = (SystemInfo*)SYSTEM_INFO_ADDRESS;
	initialize_colors();
	initialize_screen(system_info->screen_x, system_info->screen_y, system_info->vram);

	unsigned char keyboard_buffer[32];
	initialize_queue(32, keyboard_buffer, &keyboard_queue);
	out_8bit(PIC0_IMR, 0xF9); // enable pic1 and keyboard (11111001)
	out_8bit(PIC1_IMR, 0xEF); // enable mouse (11101111)

	int mouse_x = (system_info->screen_x - 16) / 2;
	int mouse_y = (system_info->screen_y - 28 - 16) / 2;
	char cursor[16 * 16];
	initialize_mouse_cursor(cursor, DARK_CYAN);
	draw_image(system_info->screen_x, 16, 16, 16, (Point){mouse_x, mouse_y}, cursor, system_info->vram);

	char string_buffer[100];
	sprintf(string_buffer, "(%d, %d)", mouse_x, mouse_y);
	print_string(system_info->screen_x, WHITE, (Point){0, 0}, string_buffer, system_info->vram);

	while (1)
	{
		cli();
		if (queue_size(&keyboard_queue) == 0)
		{
			sti_hlt();
		}
		else
		{
			int data = dequeue(&keyboard_queue);
			sti();
			sprintf(string_buffer, "%X", data);
			draw_rectangle(system_info->screen_x, DARK_CYAN, (Point){0, 16}, (Point){15, 31}, system_info->vram);
			print_string(system_info->screen_x, WHITE, (Point){0, 16}, string_buffer, system_info->vram);
		}
	}
}