#ifndef PANIC_H
#define PANIC_H 1
#include"io.h"

#define assert(expr, msg) if(!(expr)) panic(msg)
void panic(char* msg);

#endif
