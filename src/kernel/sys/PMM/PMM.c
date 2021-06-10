#include"PMM.h"

volatile uint64_t page_dir[4] __attribute__((aligned(0x20)));
volatile uint64_t page_table[512] __attribute__((aligned(0x1000)));

void PMM_init()
{
    page_table[0] = (uint64_t)&page_dir | 1;
    page_dir[0] = 0b10000011;

    asm volatile(
        "mov %0, %%cr3"
        :
        : "r"(&page_table)
    );
}
