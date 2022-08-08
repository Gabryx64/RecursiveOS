#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H 1
#include "sys/panic.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void exception_handler(uint64_t irq);
void exc_0();
void exc_1();
void exc_2();
void exc_3();
void exc_4();
void exc_5();
void exc_6();
void exc_7();
void exc_8();
void exc_10();
void exc_11();
void exc_12();
void exc_13();
void exc_14();
void exc_15();
void exc_16();
void exc_17();
void exc_18();
void exc_19();
void exc_20();
void exc_30();

#ifdef __cplusplus
}
#endif

#endif
