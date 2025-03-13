#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "descriptors.h"
#include "entrypoint.h"
#include "graphics.h"
#include "interrupts.h"
#include "memory.h"
#include "queue.h"

extern Queue keyboard_queue;
extern Queue mouse_queue;

void _main(void)
{
	initialize_gdt();
	initialize_idt();
	initialize_pic();
	sti(); // enable cpu interrupts

	unsigned char keyboard_buffer[32];
	initialize_queue(32, keyboard_buffer, &keyboard_queue);

	unsigned char mouse_buffer[128];
	initialize_queue(128, mouse_buffer, &mouse_queue);

	out_8bit(PIC0_IMR, 0xF9); // enable pic1 and keyboard (11111001)
	out_8bit(PIC1_IMR, 0xEF); // enable mouse (11101111)
	initialize_keyboard_controller();

	MouseData mouse_data;
	enable_mouse(&mouse_data);

	SystemInfo *system_info = (SystemInfo*)SYSTEM_INFO_ADDRESS;
	initialize_colors();
	initialize_screen(system_info->screen_x, system_info->screen_y, system_info->vram);

	char cursor[16 * 16];
	initialize_mouse_cursor(cursor, DARK_CYAN);

	int mouse_x = (system_info->screen_x - 16) / 2;
	int mouse_y = (system_info->screen_y - 28 - 16) / 2;
	draw_image(system_info->screen_x, 16, 16, 16, (Point){mouse_x, mouse_y}, cursor, system_info->vram);

	char string_buffer[100];
	sprintf(string_buffer, "(%d, %d)", mouse_x, mouse_y);
	print_string(system_info->screen_x, WHITE, (Point){0, 0}, string_buffer, system_info->vram);

	sprintf(string_buffer, "memory %dMB", test_memory(0x00400000, 0xBFFFFFFF) / (1024 * 1024));
	print_string(system_info->screen_x, WHITE, (Point){0, 32}, string_buffer, system_info->vram);

	while (1)
	{
		cli();
		if (queue_size(&keyboard_queue) != 0)
		{
			int data = dequeue(&keyboard_queue);
			sti();
			sprintf(string_buffer, "%X", data);
			draw_rectangle(system_info->screen_x, DARK_CYAN, (Point){0, 16}, (Point){15, 31}, system_info->vram);
			print_string(system_info->screen_x, WHITE, (Point){0, 16}, string_buffer, system_info->vram);
		}
		else if (queue_size(&mouse_queue) != 0)
		{
			int data = dequeue(&mouse_queue);
			sti();

			if (decode_mouse(data, &mouse_data) == 1)
			{
				sprintf(string_buffer, "[lcr %d %d]", mouse_data.x, mouse_data.y);
				if ((mouse_data.button & BUTTON_LEFT) != 0)
				{
					string_buffer[1] = 'L';
				}
				if ((mouse_data.button & BUTTON_MIDDLE) != 0)
				{
					string_buffer[2] = 'C';
				}
				if ((mouse_data.button & BUTTON_RIGHT) != 0)
				{
					string_buffer[3] = 'R';
				}
				draw_rectangle(system_info->screen_x, DARK_CYAN, (Point){32, 16}, (Point){32 + 15 * 8 - 1, 31}, system_info->vram);
				print_string(system_info->screen_x, WHITE, (Point){32, 16}, string_buffer, system_info->vram);

				draw_rectangle(system_info->screen_x, DARK_CYAN, (Point){mouse_x, mouse_y}, (Point){mouse_x + 15, mouse_y + 15}, system_info->vram);
				mouse_x += mouse_data.x;
				mouse_x = mouse_x < 0 ? 0 : mouse_x;
				mouse_x = mouse_x > system_info->screen_x - 16 ? system_info->screen_x - 16 : mouse_x;
				mouse_y += mouse_data.y;
				mouse_y = mouse_y < 0 ? 0 : mouse_y;
				mouse_y = mouse_y > system_info->screen_y - 16 ? system_info->screen_y - 16 : mouse_y;
				sprintf(string_buffer, "(%d, %d)", mouse_x, mouse_y);
				draw_rectangle(system_info->screen_x, DARK_CYAN, (Point){0, 0}, (Point){79, 15}, system_info->vram);
				print_string(system_info->screen_x, WHITE, (Point){0, 0}, string_buffer, system_info->vram);
				draw_image(system_info->screen_x, 16, 16, 16, (Point){mouse_x, mouse_y}, cursor, system_info->vram);
			}
		}
		else
		{
			sti_hlt();
		}
	}
}