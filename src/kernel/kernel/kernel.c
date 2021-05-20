#include<stdint.h>
#include<stddef.h>
#include<wchar.h>
#include"sys/sys.h"
#include"graphics.h"
#include"io.h"
#include"font/font.h"

Color fg_col = RGB(255, 255, 255);
Color bg_col = RGB(0, 0, 0);

void kmain(void)
{
    clearscreen(bg_col);

    puts(L"Welcome!");
    puts(L"Bienvenido!");
    puts(L"Bienvenue!");
    puts(L"Willkommen!");
    puts(L"かんげい!");
    puts(L"Benvenuto!");
    puts(L"καλως ΗΡΘΑΤΕ");
}
