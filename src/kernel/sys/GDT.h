#ifndef GDT_H
#define GDT_H 1
#include "io.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct gdt_pointer {
    uint16_t limit;
    uint64_t base;
} __attribute__((packed));

struct gdt_descriptor {
    uint16_t limit_low16;
    uint16_t base_low16;
    uint8_t base_mid8;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high8;
} __attribute__((packed));

void GDT_init();

#ifdef __cplusplus
}
#endif

#endif