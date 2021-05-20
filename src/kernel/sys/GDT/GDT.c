#include "GDT.h"

volatile struct gdt_descriptor gdt[8];
volatile struct gdt_pointer gdtr = { .limit = sizeof(gdt) - 1, .base = (uint64_t)gdt };

void GDT_load()
{
    __asm__ volatile("lgdt %0"
                     :
                     : "m"(gdtr)
                     : "memory");
    __asm__ volatile(
        "mov %%rsp, %%rax\n"
        "push $0x10\n"
        "push %%rax\n"
        " pushf\n"
        " push $0x8\n"
        " push $1f\n"
        " iretq\n"
        " 1:\n"
        " mov $0x10, %%ax\n"
        "  mov %%ax, %%ds\n"
        " mov %%ax, %%es\n"
        "mov %%ax, %%ss\n"
        "mov %%ax, %%fs\n"
        "mov %%ax, %%gs\n"

        :
        :
        : "rax", "memory");
}

void GDT_init()
{
    gdt[1] = (struct gdt_descriptor){ .access = 0b10011010, .granularity = 0b00100000 };
    gdt[2] = (struct gdt_descriptor){ .access = 0b10010010, .granularity = 0 };
    // log(INFO, "Loading GDT...");
    GDT_load();
    // log(INFO, "GDT loaded!");
}
