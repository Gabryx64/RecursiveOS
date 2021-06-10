#include"utf8.h"

void utf8_encode(uint8_t* buf, wchar_t c)
{
    size_t length = 0;

    if(c <= 127)
        length = 1;
    else if(c <= 2048)
        length = 2;
    else if(c <= 65535)
        length = 3;
    else
        length = 4;
}

void utf8_decode(utf8_t buf, wchar_t* c)
{
    
}
