#ifndef PANIC_H
#define PANIC_H 1
#include"io.h"

#define panic(msg) __panic(__FILE__, __FUNCTION__, __LINE__, msg)
void __panic(char* file, const char function[20], int line, char* msg);

#endif
