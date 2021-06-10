#ifndef LIBK_STR_H
#define LIBK_STR_H 1
#include<stddef.h>
#include<stdint.h>
#include<stdbool.h>
#include"sys/sys.h"
#include"utils.h"
#include"mathutils.h"

size_t strlen(const char*);
size_t wstrlen(const wchar_t* str); 
int memcmp(const void*, const void*, size_t);
void* memcpy(void* __restrict, const void* __restrict, size_t);
void* memmove(void*, const void*, size_t);
void* memset(void*, int, size_t);
 
#endif