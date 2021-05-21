#include"panic.h"
#include"sys.h"

void __panic(char *message)
{

    clearscreen(bg_col);

    puts(L"\033[31m------------------------------------------------------------------------\n");
    puts(L"KERNEL PANIC\n\033[0m");
    printf(L"\033[35m%s\033[0m\n", message);

    __asm__("cli");
    while (1)
        ;
}
