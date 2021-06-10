#ifndef LIBK_UTF8_H
#define LIBK_UTF8_H 1
#include<stdint.h>
#include<wchar.h>
#include"sys/sys.h"
#include"str.h"

#define IS_SURROGATE(c) ((c) >= 0xD800U && (c) <= 0xDFFFU)

typedef uint8_t* utf8_t;

void utf8_encode(utf8_t buf, wchar_t c);
void utf8_decode(utf8_t buf, wchar_t* c);

#endif
