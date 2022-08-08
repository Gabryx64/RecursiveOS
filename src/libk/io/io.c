#include "io.h"

int current_col = 0, current_row = 0;

void outb(uint16_t port, uint8_t val) {
    __asm__ volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

void outl(uint16_t port, uint32_t val) {
    __asm__ volatile("out %0, %1" : : "a"(val), "d"(port));
}

uint32_t inl(uint16_t port) {
    uint32_t ret;
    __asm__ volatile("in %1, %0" : "=a"(ret) : "d"(port));
    return ret;
}

void outw(uint16_t port, uint16_t val) {
    __asm__ volatile("outw %0, %1" : : "a"(val), "d"(port));
}

void clearterm() {
    clearscreen(bg_col);
    current_col = 0;
    current_row = 0;
}

int snapped_putch(char ch, int column, int row, Color fg, Color bg) {
    int x = column * 8, y = row * 8;

    if ((size_t)x >= _fb->width || (size_t)y >= _fb->height)
	return -1;

    putch(ch, x, y, fg, bg);

    return ch;
}

bool reading_escape_code = false;

int putchar(char ch) {
    int ret = ch;

    if (ch >= ' ') {
	ret = snapped_putch(ch, current_col, current_row, fg_col, bg_col);

	if (ret == -1)
	    return ret;

	current_col++;
    } else {
	switch (ch) {
	case '\a': {
	    // TODO: Implement "Bell"
	} break;

	case '\b': {
	    current_col--;
	    snapped_putch(' ', current_col, current_row, fg_col, bg_col);
	    current_col--;
	} break;

	case '\t': {
	    current_col += 4;
	} break;

	case '\f': {
	    clearterm();
	} break;

	case '\v': {
	    current_row++;
	} break;

	case '\n': {
	    current_row++;
	    current_col = 0;
	} break;

	case '\r': {
	    current_col = 0;
	} break;

	case '\e': {
	    // TODO: Implement ANSI Escape Codes
	} break;
	}
    }

    while ((size_t)current_col >= _fb->width) {
	current_col = 0;
	current_row++;
    }

    if ((size_t)current_row >= _fb->height)
	return -1;

    return ret;
}

static bool print(const char* data, size_t length) {
    for (size_t i = 0; i < length; i++) {
	if (putchar(data[i]) == EOF)
	    return false;
    }

    return true;
}

int printf(const char* format, ...) {
    va_list parameters;
    va_start(parameters, format);

    int written = 0;

    while (*format != '\0') {
	size_t maxrem = INT_MAX - written;

	if (format[0] != '%' || format[1] == '%') {
	    if (format[0] == '%')
		format++;

	    size_t amount = 1;

	    while (format[amount] && format[amount] != '%')
		amount++;

	    if (maxrem < amount)
		return -1;

	    if (!print(format, amount))
		return -1;

	    format += amount;
	    written += amount;

	    continue;
	}

	const char* format_begun_at = format++;

	if (*format == 'c') {
	    format++;
	    char c = (char)va_arg(parameters, int);

	    if (!maxrem)
		return -1;

	    if (!print((char*)&c, 1))
		return -1;
	    written++;
	} else if (*format == 's') {
	    format++;

	    const char* str = va_arg(parameters, const char*);
	    size_t len = strlen(str);

	    if (maxrem < len)
		return -1;

	    if (!print((char*)str, len))
		return -1;

	    written += len;
	} else {
	    format = format_begun_at;
	    size_t len = strlen(format);

	    if (maxrem < len)
		return -1;

	    if (!print(format, len))
		return -1;

	    written += len;
	    format += len;
	}
    }

    va_end(parameters);
    return written;
}
