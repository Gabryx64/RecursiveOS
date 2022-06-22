KERNEL := kernel.elf

ASSEMBLER = nasm

CFLAGS = -Wall -Wextra -Werror -Wno-stringop-overflow -O2 -pipe
CXXFLAGS = -Wall -Wextra -Werror -Wno-stringop-overflow -O2 -pipe

INTERNALLDFLAGS := 			\
	-pie					\
	--no-dynamic-linker		\
	-nostdlib    			\
	-Tlinker.ld  			\
	-static					\
	-zmax-page-size=0x1000	\
	-ztext

INTERNALCFLAGS  :=     						\
	-I.										\
	-Wno-unused-parameter					\
	-Ikernel/								\
	-Ikernel/graphics						\
	$(foreach d, $(wildcard libk/**), -I$d)	\
	-std=gnu99        						\
	-nostdlib    							\
	-ffreestanding     						\
	-fno-stack-protector 					\
	-fno-pic -fpie    						\
	-mno-red-zone							\
	-MMD

INTERNALCXXFLAGS  :=     					\
	-I.										\
	-Wno-unused-parameter					\
	-Ikernel/								\
	-Ikernel/graphics						\
	$(foreach d, $(wildcard libk/**), -I$d)	\
	-std=gnu++11        					\
	-nostdlib    							\
	-ffreestanding     						\
	-fno-stack-protector 					\
	-fno-pic -fpie    						\
	-mno-red-zone							\
	-MMD

CFILES     := $(shell find ./ -type f -name '*.c')
CXXFILES   := $(shell find ./ -type f -name '*.cpp')
ASMFILES   := $(shell find ./ -type f -name '*.asm')
OBJS       := $(CFILES:.c=.o) $(CXXFILES:.cpp=.o) $(ASMFILES:.asm=.o)
DEPS       := $(CFILES:.c=.d) $(CXXFILES:.cpp=.d)

.PHONY: all clean
all: $(KERNEL)

$(KERNEL): $(OBJS)
	$(LD) $(INTERNALLDFLAGS) $(OBJS) -o $@

stivale2.h:
	wget https://github.com/stivale/stivale/raw/master/stivale2.h

%.o: %.cpp stivale2.h
	$(CXX) $(CXXFLAGS) $(INTERNALCXXFLAGS) -c $< -o $@

%.o: %.c stivale2.h
	$(CC) $(CFLAGS) $(INTERNALCFLAGS) -c $< -o $@

%.o: %.asm
	$(ASSEMBLER) -felf64 $< -o $@

clean:
	$(RM) -rf $(KERNEL)
	$(RM) -rf $(OBJS)
	$(RM) -rf $(DEPS)
