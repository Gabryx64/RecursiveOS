KERNEL := kernel.elf

CC = clang
ASSEMBLER = nasm

CFLAGS = -Wall -Wextra -Ofast -Os -pipe -target x86_64-unknown-pc -g

INTERNALLDFLAGS := 								\
	-fno-pic -fno-pie							\
	-Wl,-static,--no-dynamic-linker,-ztext		\
	-nostdlib      								\
	-Tlinker.ld    								\
	-z max-page-size=0x1000

INTERNALCFLAGS  :=       						\
	-I.											\
	-Ikernel/									\
	-Ikernel/graphics							\
	$(foreach d, $(wildcard libk/**), -I$d)		\
	-std=gnu17           						\
	-nostdlib      								\
	-ffreestanding       						\
	-fno-stack-protector 						\
	-fno-pic -fpie      						\
	-mno-red-zone

CFILES := $(shell find ./ -type f -name '*.c')
ASMFILES := $(shell find ./ -type f -name '*.asm')
OBJ    := $(CFILES:.c=.o) $(ASMFILES:.asm=.o)

.PHONY: all clean

all: $(KERNEL)

$(KERNEL): $(OBJ)
	$(CC) $(INTERNALLDFLAGS) $(OBJ) -o $@

stivale2.h:
	wget https://github.com/stivale/stivale/raw/master/stivale2.h

%.o: %.c stivale2.h
	$(CC) $(CFLAGS) $(INTERNALCFLAGS) -c $< -o $@

%.o: %.asm
	$(ASSEMBLER) -felf64 $< -o $@

clean:
	rm -rf $(KERNEL) $(shell find ./ -type f -name '*.o') $(shell find ./ -type f -name '*.elf')
