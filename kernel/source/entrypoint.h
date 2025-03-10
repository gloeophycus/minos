#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#define SYSTEM_INFO_ADDRESS 0x00000FF0;

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

#endif