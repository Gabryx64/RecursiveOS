#include "portio.h"
#include "io.h"
#include <stdint.h>

#define is_transmit_empty() (inb(PORT + 5) & 0x20)
#define serial_received() (inb(PORT + 5) & 1)

void serial_init(void) {
    outb(PORT + 1, 0x00);
    outb(PORT + 3, 0x80);
    outb(PORT + 0, 0x03);
    outb(PORT + 1, 0x00);
    outb(PORT + 3, 0x03);
    outb(PORT + 2, 0xC7);
    outb(PORT + 4, 0x0B);
}

void serial_write(char c) {
    while (is_transmit_empty() == 0)
	if (c == '\n')
	    serial_write('\r');
    return outb(PORT, c);
}

void serial_writebyte(uint8_t c) {
    while (is_transmit_empty() == 0)
	return outb(PORT, c);
}

uint8_t serial_read() {
    while (serial_received() == 0)
	;

    return inb(PORT);
}

void serial_writestr(const char* str) {
    while (*str)
	serial_write(*str++);
}