#include "graphics.h"

void set_colors(int size, const RGB *colors)
{
	int eflags = load_eflags();
	cli();
	out_8bit(WRITE_ADDRESS_REGISTER, 0);
	for (int i = 0; i < size; i++)
	{
		out_8bit(DATA_REGISTER, colors[i].red / 4);
		out_8bit(DATA_REGISTER, colors[i].green / 4);
		out_8bit(DATA_REGISTER, colors[i].blue / 4);
	}
	store_eflags(eflags);
}

void initialize_colors(void)
{
	const RGB colors[16] = {
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
	set_colors(sizeof(colors) / sizeof(*colors), colors);
}

void initialize_screen(int x, int y, unsigned char *vram)
{
	draw_rectangle(x, DARK_CYAN, (Point){0, 0}, (Point){x - 1, y - 29}, vram);
	draw_rectangle(x, GRAY, (Point){0, y - 28}, (Point){x - 1, y - 28}, vram);
	draw_rectangle(x, WHITE, (Point){0, y - 27}, (Point){x - 1, y - 27}, vram);
	draw_rectangle(x, GRAY, (Point){0, y - 26}, (Point){x - 1, y - 1}, vram);
	draw_rectangle(x, WHITE, (Point){3, y - 24}, (Point){59, y - 24}, vram);
	draw_rectangle(x, WHITE, (Point){2, y - 24}, (Point){2, y - 4}, vram);
	draw_rectangle(x, DARK_GRAY, (Point){3, y - 4}, (Point){59, y - 4}, vram);
	draw_rectangle(x, DARK_GRAY, (Point){59, y - 23}, (Point){59, y - 5}, vram);
	draw_rectangle(x, BLACK, (Point){2, y - 3}, (Point){59, y - 3}, vram);
	draw_rectangle(x, BLACK, (Point){60, y - 24}, (Point){60, y - 3}, vram);
	draw_rectangle(x, DARK_GRAY, (Point){x - 47, y - 24}, (Point){x - 4, y - 24}, vram);
	draw_rectangle(x, DARK_GRAY, (Point){x - 47, y - 23}, (Point){x - 47, y - 4}, vram);
	draw_rectangle(x, WHITE, (Point){x - 47, y - 3}, (Point){x - 4, y - 3}, vram);
	draw_rectangle(x, WHITE, (Point){x - 3, y - 24}, (Point){x - 3, y - 3}, vram);
}

void initialize_mouse_cursor(char *buffer, char background_color)
{
    const char cursor[16][16] = {
		"**************..",
		"*OOOOOOOOOOO*...",
		"*OOOOOOOOOO*....",
		"*OOOOOOOOO*.....",
		"*OOOOOOOO*......",
		"*OOOOOOO*.......",
		"*OOOOOOO*.......",
		"*OOOOOOOO*......",
		"*OOOO**OOO*.....",
		"*OOO*..*OOO*....",
		"*OO*....*OOO*...",
		"*O*......*OOO*..",
		"**........*OOO*.",
		"*..........*OOO*",
		"............*OO*",
		".............***",
	};

    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            switch (cursor[i][j])
            {
            case '*':
                buffer[i * 16 + j] = BLACK;
                break;
            case 'O':
                buffer[i * 16 + j] = WHITE;
                break;
            case '.':
                buffer[i * 16 + j] = background_color;
                break;
            }
        }
    }
}

void draw_rectangle(int screen_x, int color, Point point_1, Point point_2, unsigned char *vram)
{
	for (int y = point_1.y; y <= point_2.y; y++)
	{
		for (int x = point_1.x; x <= point_2.x; x++)
		{
			vram[x + y * screen_x] = color;
		}
	}
}

void draw_image(int screen_x, int image_x, int image_y, int buffer_x, Point point, const char *buffer, unsigned char *vram)
{
    for (int y = 0; y < image_y; y++)
    {
        for (int x = 0; x < image_x; x++)
        {
            vram[(point.y + y) * screen_x + (point.x + x)] = buffer[y * buffer_x + x];
        }
    }
}

// __attribute__((optimize("O0")))
void print_character(int screen_x, int color, Point point, const unsigned char *font, unsigned char *vram)
{
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (font[i] & (0x80 >> j))
			{
				vram[(point.y + i) * screen_x + point.x + j] = color;
			}
		}
	}
}

void print_string(int screen_x, int color, Point point, const char *string, unsigned char *vram)
{
    extern const unsigned char fonts[][16];
	for (int i = 0; string[i] != '\0'; i++)
	{
		print_character(screen_x, color, point, fonts[(unsigned char)string[i]], vram);
		point.x += 8;
	}
}