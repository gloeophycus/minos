#include "graphics.h"

void _main(void)
{
	initialize_palette();

	SystemInfo *system_info = (SystemInfo *)0x0FF0;
	initialize_screen(system_info->vram, system_info->screen_x, system_info->screen_y);

	while (1)
	{
		hlt();
	}
}