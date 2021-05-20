#ifndef LIBK_STDIO_H
#define LIBK_STDIO_H 1
#include<stdint.h>
#include<wchar.h>
#include<limits.h>
#include<stdbool.h>
#include<stdarg.h>
#include"graphics.h"
#include"str.h"

#define EOF (-1)

extern int current_col, current_row;

int snapped_putch(wchar_t ch, int column, int row, Color fg, Color bg);
int putchar(wchar_t ch);
int printf(const wchar_t* restrict format, ...);
int puts(wchar_t* str);

#endif