#ifndef GRAPHICS_H
#define GRAPHICS_H 1
#include<stdint.h>
#include<stivale2.h>
#include<wchar.h>
#include"sys/sys.h"

#define RGB(r, g, b) (Color){ r, g, b }
#define getcolor(col) (((col.r & 0xff) << fb_tag->red_mask_shift) + ((col.g & 0xff) << fb_tag->green_mask_shift) + ((col.b & 0xff) << fb_tag->blue_mask_shift))

typedef struct
{
    uint8_t r, g, b;
} Color;

extern Color fg_col;
extern Color bg_col;

void putpixel(int x, int y, Color color);
void clearscreen(Color col);
void putch(wchar_t ch, int x, int y, Color fg, Color bg);

#endif
