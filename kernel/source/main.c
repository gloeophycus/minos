#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "descriptors.h"
#include "graphics.h"

extern const unsigned char fonts[][16];

void _main(void)
{
	initialize_gdt();
	initialize_idt();
	initialize_colors();

	SystemInfo *system_info = (SystemInfo *)0x0FF0;
	initialize_screen(system_info->screen_x, system_info->screen_y, system_info->vram);

	int mouse_x = (system_info->screen_x - 16) / 2;
	int mouse_y = (system_info->screen_y - 28 - 16) / 2;
	char cursor[16 * 16];
	initialize_mouse_cursor(cursor, DARK_CYAN);
	draw_image(system_info->screen_x, 16, 16, 16, (Point){mouse_x, mouse_y}, cursor, system_info->vram);

	char buffer[100];
	sprintf(buffer, "(%d, %d)", mouse_x, mouse_y);
	print_string(system_info->screen_x, WHITE, (Point){0, 0}, (unsigned char*)buffer, system_info->vram);

	while (1)
	{
		hlt();
	}
}