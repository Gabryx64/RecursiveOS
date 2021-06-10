#ifndef PMM_H
#define PMM_H 1
#include<stdint.h>

extern volatile uint64_t page_dir[4] __attribute__((aligned(0x20)));
extern volatile uint64_t page_table[512] __attribute__((aligned(0x1000)));

void PMM_init();

#endif
