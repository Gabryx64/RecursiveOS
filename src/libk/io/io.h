#ifndef LIBK_STDIO_H
#define LIBK_STDIO_H 1
#include<stdint.h>
#include<stdlib.h>
#include<limits.h>
#include<stdbool.h>
#include<stdarg.h>
#include"graphics.h"
#include"str.h"

#define EOF (-1)

extern int current_col, current_row;
extern Color fg_col, bg_col;

void outb(uint16_t port, uint8_t val);
uint8_t inb(uint16_t port);
void outl(uint16_t port, uint32_t val);
uint32_t inl(uint16_t port);
void outw(uint16_t port, uint16_t val);

void clearterm();
int snapped_putch(wchar_t ch, int column, int row, Color fg, Color bg);
int putchar(wchar_t ch);
int printf(const char* restrict format, ...);
#define puts(str) printf("%s\n", str);

#endif
