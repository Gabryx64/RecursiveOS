#include "IDT.h"

static volatile struct idt_descriptor idt[256];
static volatile struct idt_pointer idtr = { .size = 256 * sizeof(struct idt_descriptor), .addr = (uint64_t)idt };

void PIC_remap(void)
{
    outb(0x20, 0x11);
    outb(0xA0, 0x11);

    outb(0x21, 0x20);
    outb(0xA1, 0x28);

    outb(0x21, 0x04);
    outb(0xA1, 0x02);

    outb(0x21, 0x01);
    outb(0xA1, 0x01);

    outb(0x21, 0x0);
    outb(0xA1, 0x0);
    puts(L"IRQs Remapped");
}

static struct idt_descriptor idt_make_entry(uint64_t offset)
{
    return (struct idt_descriptor)
    {
        .selector = 0x08,
        .offset_lo = offset & 0xFFFF,
        .offset_mid = (offset >> 16) & 0xFFFF,
        .offset_hi = (offset >> 32) & 0xFFFFFFFF,
        .ist = 0,
        .zero = 0,
        .type_attr = 0x8e
    };
}

void ISR_init()
{
    PIC_remap();

    for (int i = 0x23; i < 0x28; i++)
    {
        idt[i] = idt_make_entry((uint64_t)&isr_irq_master);
    }

    for (int i = 0x28; i < 0x2F; i++)
    {
        idt[i] = idt_make_entry((uint64_t)&isr_irq_slave);
    }
}

void IDT_load()
{
    asm volatile("lidt %0"
                    :
                    : "m"(idtr));
}

void IDT_init()
{
    puts(L"Initializing IDT...");
    puts(L"Loading ISR...");
    ISR_init();
    puts(L"Loading IDT...");
    IDT_load();
    puts(L"IDT loaded!");
    asm volatile("sti");
}
