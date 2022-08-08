#include "exceptions.h"

static char* exceptions[] = {
    [0] = "Unhandled Exception: Division by Zero",
    [1] = "Unhandled Exception: Debug",
    [2] = "Unhandled Exception: Non Maskable Interrupt",
    [3] = "Unhandled Exception: Breakpoint",
    [4] = "Unhandled Exception: Overflow",
    [5] = "Unhandled Exception: Bound Range Exceeded",
    [6] = "Unhandled Exception: Invalid opcode",
    [7] = "Unhandled Exception: Device not available",
    [8] = "Unhandled Exception: Double Fault",
    [10] = "Unhandled Exception: Invalid TSS",
    [11] = "Unhandled Exception: Segment not present",
    [12] = "Unhandled Exception: Stack Exception",
    [13] = "Unhandled Exception: General Protection fault",
    [14] = "Unhandled Exception: Page fault",
    [16] = "Unhandled Exception: x87 Floating Point Exception",
    [17] = "Unhandled Exception: Alignment check",
    [18] = "Unhandled Exception: Machine check",
    [19] = "Unhandled Exception: SIMD floating point Exception",
    [20] = "Unhandled Exception: Virtualization Exception",
    [30] = "Unhandled Exception: Security Exception"};

#define exc(num)                                                               \
    void exc_##num() { exception_handler(num); }

void exception_handler(uint64_t irq) {
    __asm__ volatile("cli");
    panic(exceptions[irq]);
}

exc(0) exc(1) exc(2) exc(3) exc(4) exc(5) exc(6) exc(7) exc(8) exc(10) exc(11)
    exc(12) exc(13) exc(14) exc(15) exc(16) exc(17) exc(18) exc(19) exc(20)
	exc(30)
