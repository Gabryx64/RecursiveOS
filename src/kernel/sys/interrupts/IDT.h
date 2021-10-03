#ifndef IDT_H
#define IDT_H 1
#include<stddef.h>
#include<stdint.h>
#include<io.h>

extern void isr(void);
extern void isr_irq_master(void);
extern void isr_irq_slave(void);

struct idt_descriptor
{
  uint16_t offset_lo;
  uint16_t selector;
  uint8_t ist;
  uint8_t type_attr;
  uint16_t offset_mid;
  uint32_t offset_hi;
  uint32_t zero;
} __attribute__((packed));

struct idt_pointer
{
  uint16_t size;
  uint64_t addr;
} __attribute__((packed));

void IDT_init();

#endif
