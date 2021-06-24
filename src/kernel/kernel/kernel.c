#include<stdint.h>
#include<stddef.h>
#include<wchar.h>
#include"sys/sys.h"
#include"graphics.h"
#include"io.h"
#include"mathutils.h"
#include"font/font.h"
#include"utf8.h"

Color fg_col, bg_col;

void kmain(void)
{
    fg_col = UINT_RGB(0x887ECB);
    bg_col = UINT_RGB(0x50459B);

    clearterm();

    /*
    utf8_t utest = {0};
    wchar_t wtest = 0;

    utf8_encode(utest, 'a');
    utf8_decode(utest, &wtest);

    printf(L"%lc\n", wtest);

    TODO: create utf8 encoder and decoder
    */

    puts(L"Welcome!");
    puts(L"Bienvenido!");
    puts(L"Bienvenue!");
    puts(L"Willkommen!");
    puts(L"かんげい!");
    puts(L"Benvenuto!");
}
