#ifndef PANIC_H
#define PANIC_H 1
#include<stdint.h>
#include"io.h"

void __panic(char *message);

#define panic(msg) __panic(msg);

#endif
