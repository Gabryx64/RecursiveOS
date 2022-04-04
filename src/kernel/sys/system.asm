bits 64
section .text

global isr
global isr_irq_master
global isr_irq_slave

isr:


isr_irq_master:
	mov al, 0x20
	out 0x20, al
	iretq

isr_irq_slave:
	mov al, 0x20
	out 0xa0, al
	out 0x20, al
	iretq
