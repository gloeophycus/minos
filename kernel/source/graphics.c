#include "graphics.h"

void initialize_palette(void)
{
	static RGB palette[16] = {
		{0x00, 0x00, 0x00}, // black
		{0xFF, 0x00, 0x00}, // red
		{0x00, 0xFF, 0x00}, // green
		{0x00, 0x00, 0xFF}, // blue
		{0xFF, 0xFF, 0x00}, // yellow
		{0xFF, 0x00, 0xFF}, // purple
		{0x00, 0xFF, 0xFF}, // cyan
		{0xFF, 0xFF, 0xFF}, // white
		{0xC6, 0xC6, 0xC6}, // gray
		{0x84, 0x00, 0x00}, // dark red
		{0x00, 0x84, 0x00}, // dark green
		{0x00, 0x00, 0x84}, // dark blue
		{0x84, 0x84, 0x00}, // dark yello
		{0x84, 0x00, 0x84}, // dark purple
		{0x00, 0x84, 0x84}, // dark cyan
		{0x84, 0x84, 0x84}, // dark gray
	};
	set_palette(sizeof(palette) / sizeof(*palette), palette);
}

void set_palette(int size, RGB *palette)
{
	int eflags = load_eflags();
	cli();
	out_8bit(WRITE_ADDRESS_REGISTER, 0);
	for (int i = 0; i < size; i++)
	{
		out_8bit(DATA_REGISTER, palette[i].red / 4);
		out_8bit(DATA_REGISTER, palette[i].green / 4);
		out_8bit(DATA_REGISTER, palette[i].blue / 4);
	}
	store_eflags(eflags);
}

void initialize_screen(unsigned char *vram, int x, int y)
{
	draw_rectangle(vram, x, DARK_CYAN, (Point){0, 0}, (Point){x - 1, y - 29});
	draw_rectangle(vram, x, GRAY, (Point){0, y - 28}, (Point){x - 1, y - 28});
	draw_rectangle(vram, x, WHITE, (Point){0, y - 27}, (Point){x - 1, y - 27});
	draw_rectangle(vram, x, GRAY, (Point){0, y - 26}, (Point){x - 1, y - 1});
	draw_rectangle(vram, x, WHITE, (Point){3, y - 24}, (Point){59, y - 24});
	draw_rectangle(vram, x, WHITE, (Point){2, y - 24}, (Point){2, y - 4});
	draw_rectangle(vram, x, DARK_GRAY, (Point){3, y - 4}, (Point){59, y - 4});
	draw_rectangle(vram, x, DARK_GRAY, (Point){59, y - 23}, (Point){59, y - 5});
	draw_rectangle(vram, x, BLACK, (Point){2, y - 3}, (Point){59, y - 3});
	draw_rectangle(vram, x, BLACK, (Point){60, y - 24}, (Point){60, y - 3});
	draw_rectangle(vram, x, DARK_GRAY, (Point){x - 47, y - 24}, (Point){x - 4, y - 24});
	draw_rectangle(vram, x, DARK_GRAY, (Point){x - 47, y - 23}, (Point){x - 47, y - 4});
	draw_rectangle(vram, x, WHITE, (Point){x - 47, y - 3}, (Point){x - 4, y - 3});
	draw_rectangle(vram, x, WHITE, (Point){x - 3, y - 24}, (Point){x - 3, y - 3});
}

void draw_rectangle(unsigned char *vram, int x_size, int color, Point point_1, Point point_2)
{
	for (int y = point_1.y; y <= point_2.y; y++)
	{
		for (int x = point_1.x; x <= point_2.x; x++)
		{
			vram[x + y * x_size] = color;
		}
	}
}