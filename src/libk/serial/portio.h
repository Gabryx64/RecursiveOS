#include <stdint.h>
#ifndef LIBK_PORTIO_H
#define LIBK_PORTIO_H 1
#include<stddef.h>

#define PORT 0x3f8

#ifdef __cplusplus
extern "C" {
#endif

void serial_init(void);
void serial_write(char c);
void serial_writebyte(uint8_t c);
uint8_t serial_read();
void serial_writestr(const char* str);

#ifdef __cplusplus
}
#endif

#endif
