#ifndef PANIC_H
#define PANIC_H 1
#include "io.h"

#ifdef __cplusplus
extern "C" {
#endif

#define assert(expr, msg)                                                      \
    if (!(expr))                                                               \
    panic(msg)
void panic(const char* msg);

#ifdef __cplusplus
}
#endif

#endif
