#include"vec.hpp"
#include"io.h"
#include"portio.h"

extern "C" void kmain()
{
    libk::Vec<char> x = { 'h', 'e', 'l', 'l', 'o', '!', '\n' };
    x.push('\0');
    printf("%s", x.begin());
}
