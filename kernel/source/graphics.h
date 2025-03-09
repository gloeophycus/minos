#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "assembly_functions.h"

enum Color
{
	BLACK,
	RED,
	GREEN,
	BLUE,
	YELLOW,
	PURPLE,
	CYAN,
	WHITE,
	GRAY,
	DARK_RED,
	DARK_GREEN,
	DARK_BLUE,
	DARK_YELLOW,
	DARK_PURPLE,
	DARK_CYAN,
	DARK_GRAY,
};

enum DAC
{
	READ_ADDRESS_REGISTER = 0x03C7,
	WRITE_ADDRESS_REGISTER = 0x03C8,
	DATA_REGISTER = 0x03C9,
};

typedef struct __attribute__((packed))
{
	unsigned char red;
	unsigned char green;
	unsigned char blue;
} RGB;

typedef struct
{
	char sectors;
	char leds;
	char vmode;
	char reserve;
	short screen_x;
	short screen_y;
	unsigned char *vram;
} SystemInfo;

typedef struct
{
	int x;
	int y;
} Point;

void set_colors(int size, const RGB *colors);
void initialize_colors(void);
void draw_rectangle(unsigned char *vram, int screen_x, int color, Point point_1, Point point_2);
void initialize_screen(unsigned char *vram, int x, int y);

#endif