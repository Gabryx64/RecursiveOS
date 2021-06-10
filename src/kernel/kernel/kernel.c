#include<stdint.h>
#include<stddef.h>
#include<wchar.h>
#include"sys/sys.h"
#include"graphics.h"
#include"io.h"
#include"mathutils.h"
#include"font/font.h"
#include"utf8.h"

Color fg_col = RGB(136, 126, 203);
Color bg_col = RGB(80, 69, 155);

void kmain(void)
{
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
    puts(L"καλώς ήρθατε");

    while(1)
        ;
}
