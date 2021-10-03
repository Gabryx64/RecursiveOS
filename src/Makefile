KERNEL := kernel.elf

ASSEMBLER = nasm

CFLAGS = -Wall -Wextra -Werror -Ofast -pipe

INTERNALLDFLAGS := 													\
	-pie																			\
	--no-dynamic-linker												\
	-nostdlib    															\
	-Tlinker.ld  															\
	-static																		\
	-zmax-page-size=0x1000										\
	-ztext

INTERNALCFLAGS  :=     											\
	-I.																				\
	-Ikernel/																	\
	-Ikernel/graphics													\
	$(foreach d, $(wildcard libk/**), -I$d)		\
	-std=gnu99       													\
	-nostdlib    															\
	-ffreestanding     												\
	-fno-stack-protector 											\
	-fno-pic -fpie    												\
	-mno-red-zone															\
	-MMD

CFILES := $(shell find ./ -type f -name '*.c')
ASMFILES := $(shell find ./ -type f -name '*.asm')
OBJ  := $(CFILES:.c=.o) $(ASMFILES:.asm=.o)

.PHONY: all clean

all: $(KERNEL)

$(KERNEL): $(OBJ)
	$(LD) $(INTERNALLDFLAGS) $(OBJ) -o $@

stivale2.h:
	wget https://github.com/stivale/stivale/raw/master/stivale2.h

%.o: %.c stivale2.h
	$(CC) $(CFLAGS) $(INTERNALCFLAGS) -c $< -o $@

%.o: %.asm
	$(ASSEMBLER) -felf64 $< -o $@

clean:
	rm -rf $(KERNEL) $(shell find ./ -type f -name '*.o') $(shell find ./ -type f -name '*.d') $(shell find ./ -type f -name '*.elf')