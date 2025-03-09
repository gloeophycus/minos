#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graphics.h"

extern const unsigned char fonts[][16];

// __attribute__((optimize("O0")))
void print_character(unsigned char *vram, int screen_x, int x, int y, int color, const unsigned char *font)
{
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (font[i] & (0x80 >> j))
			{
				vram[(y + i) * screen_x + x + j] = color;
			}
		}
	}
}

void print_string(unsigned char *vram, int screen_x, int x, int y, int color, const unsigned char *string)
{
	for (int i = 0; string[i] != '\0'; i++)
	{
		print_character(vram, screen_x, x, y, color, fonts[string[i]]);
		x += 8;
	}
}

void _main(void)
{
	initialize_colors();

	SystemInfo *system_info = (SystemInfo *)0x0FF0;
	initialize_screen(system_info->vram, system_info->screen_x, system_info->screen_y);

	while (1)
	{
		hlt();
	}
}