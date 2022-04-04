#ifndef LIBK_STR_H
#define LIBK_STR_H 1
#include<stddef.h>
#include<stdint.h>
#include<stdbool.h>
#include"sys/sys.h"
#include"utils.h"
#include"mathutils.h"

#define stringify(x) #x
#define to_string(x) stringify(x)

size_t strlen(const char*);
int memcmp(const void*, const void*, size_t);
void* memcpy(void* __restrict, const void* __restrict, size_t);
void* memmove(void*, const void*, size_t);
void* memset(void*, uint8_t, size_t);

char* btoa(char buf[4],   unsigned char n);
char* stoa(char buf[7],   short n);
char* ustoa(char buf[7],  unsigned short n);
char* itoa(char buf[12],  int n);
char* utoa(char buf[11],  unsigned n);
char* ltoa(char buf[21],  long n);
char* ultoa(char buf[21], unsigned long n);
 
#endif