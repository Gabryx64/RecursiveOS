#ifndef GRAPHICS_H
#define GRAPHICS_H 1
#include<stdint.h>
#include<stivale2.h>
#include"sys/sys.h"

#ifdef __cplusplus
extern "C" {
#endif

#define RGB(r, g, b) (Color){ r, g, b }
#define getcolor(col) (((col.r & 0xff) << fb_tag->red_mask_shift) + ((col.g & 0xff) << fb_tag->green_mask_shift) + ((col.b & 0xff) << fb_tag->blue_mask_shift))

typedef struct
{
  uint8_t r, g, b;
} Color;

Color UINT_RGB(uint32_t color);
void putpixel(int x, int y, Color color);
void clearscreen(Color col);
void putch(char ch, int x, int y, Color fg, Color bg);
void draw_line(int x0, int y0, int x1, int y1, Color col);

#ifdef __cplusplus
}
#endif

#endif
