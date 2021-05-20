#include"graphics.h"
#include"font/font.h"

void putpixel(int x, int y, Color color)
{
    fb[x + y * 640] = getcolor(color);
}

void clearscreen(Color col)
{
    int x, y;
    for(y = 0; y < 480; y++)
    {
        for(x = 0; x < 640; x++)
        {
            putpixel(x, y, col);
        }
    }
}

void putch(wchar_t ch, int x, int y, Color fg, Color bg)
{
    for(int i = 0; i < 8; i++)
    {
        if(y + i >= 480)
            break;

        for(int j = 0; j < 8; j++)
        {
            if(x + j >= 640)
                break;

            putpixel(x + j, y + i, ((font[ch][i] >> j) & 1) == 1 ? fg : bg);
        }
    }
}
