#include"exceptions.h"

static char* exceptions[] =
{
  [0]  = "Division by Zero",
  [1]  = "Debug",
  [2]  = "Non Maskable Interrupt",
  [3]  = "Breakpoint",
  [4]  = "Overflow",
  [5]  = "Bound Range Exceeded",
  [6]  = "Invalid opcode",
  [7]  = "Device not available",
  [8]  = "Double Fault",
  [10] = "Invalid TSS",
  [11] = "Segment not present",
  [12] = "Stack Exception",
  [13] = "General Protection fault",
  [14] = "Page fault",
  [16] = "x87 Floating Point Exception",
  [17] = "Alignment check",
  [18] = "Machine check",
  [19] = "SIMD floating point Exception",
  [20] = "Virtualization Exception",
  [30] = "Security Exception"
};

#define exc(num) void exc_##num() { exception_handler(num); }

void exception_handler(uint64_t irq)
{
  asm volatile("cli");
  panic(exceptions[irq]);
}

exc(0)
exc(1)
exc(2)
exc(3)
exc(4)
exc(5)
exc(6)
exc(7)
exc(8)
exc(10)
exc(11)
exc(12)
exc(13)
exc(14)
exc(15)
exc(16)
exc(17)
exc(18)
exc(19)
exc(20)
exc(30)
