#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graphics.h"

extern const unsigned char fonts[][16];

void _main(void)
{
	initialize_colors();

	SystemInfo *system_info = (SystemInfo *)0x0FF0;
	initialize_screen(system_info->screen_x, system_info->screen_y, system_info->vram);

    char cursor[16 * 16];
    initialize_mouse_cursor(cursor, DARK_CYAN);
    draw_image(system_info->screen_x, 16, 16, 16, (Point){152, 78}, cursor, system_info->vram);

	while (1)
	{
		hlt();
	}
}