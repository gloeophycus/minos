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

enum DAC // digital to analog converter
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
	int x;
	int y;
} Point;

void set_colors(int size, const RGB *colors);
void initialize_colors(void);
void initialize_screen(int x, int y, unsigned char *vram);
void initialize_mouse_cursor(char *buffer, char background_color);
void draw_rectangle(int screen_x, int color, Point point_1, Point point_2, unsigned char *vram);
void draw_image(int screen_x, int image_x, int image_y, int buffer_x, Point point, const char *buffer, unsigned char *vram);
void print_character(int screen_x, int color, Point point, const unsigned char *font, unsigned char *vram);
void print_string(int screen_x, int color, Point point, const char *string, unsigned char *vram);

#endif