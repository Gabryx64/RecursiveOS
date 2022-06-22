#include"graphics.h"
#include"font/font.h"
#include"mathutils.h"

#include<stddef.h>

Color UINT_RGB(uint32_t color)
{
  uint8_t* col = (uint8_t*)&color;

  return RGB(col[2], col[1], col[0]);
}

void putpixel(int x, int y, Color color)
{
  fb[x + y * _fb->width] = getcolor(color);
}

void clearscreen(Color col)
{
  
  int x, y;
  for(y = 0; (size_t)y < _fb->height; y++)
  {
    for(x = 0; (size_t)x < _fb->width; x++)
    {
      putpixel(x, y, col);
    }
  }
}

void putch(char ch, int x, int y, Color fg, Color bg)
{
  for(int i = 0; i < 8; i++)
  {
    if((size_t)(y + i) >= _fb->height)
      break;

    for(int j = 0; j < 8; j++)
    {
      if((size_t)(x + j) >= _fb->width)
        break;

      putpixel(x + j, y + i, ((font[(uint8_t)ch][i] >> j) & 1) == 1 ? fg : bg);
    }
  }
}

void draw_line_low(int x0, int y0, int x1, int y1, Color col)
{
  int dx = x1 - x0;
  int dy = y1 - y0;
  int yi = 1;
  if(dy < 0)
  {
    yi = -1;
    dy = -dy;
  }

  int D = (2 * dy) - dx;
  int y = y0;

  for(int x = x0; x < x1; x++)
  {
    putpixel(x, y, col);
    if(D > 0)
    {
      y += yi;
      D += 2 * (dy - dx);
    }
    else
    {
      D += 2 * dy;
    }
  }
}

void draw_line_high(int x0, int y0, int x1, int y1, Color col)
{
  int dx = x1 - x0;
  int dy = y1 - y0;
  int xi = 1;
  if(dx < 0)
  {
    xi = -1;
    dx = -dx;
  }

  int D = (2 * dx) - dy;
  int x = x0;

  for (int y = y0; y < y1; y++)
  {
    putpixel(x, y, col);
    if(D > 0)
    {
      x += xi;
      D += 2 * (dx - dy);
    }
    else
    {
      D += 2 * dx;
    }
  }
}

void draw_line(int x0, int y0, int x1, int y1, Color col)
{
  if(abs(y1 - y0) < abs(x1 - x0))
  {
    if(x0 > x1)
      draw_line_low(x1, y1, x0, y0, col);
    else
      draw_line_low(x0, y0, x1, y1, col);
  }
  else
  {
    if(y0 > y1)
      draw_line_high(x1, y1, x0, y0, col);
    else
      draw_line_high(x0, y0, x1, y1, col);
  }
}
