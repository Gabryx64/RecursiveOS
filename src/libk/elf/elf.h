#ifndef LIBK_ELF_H
#define LIBK_ELF_H 1
#include <stdbool.h>
#include <stdint.h>

#define ELF_MAGIC_LE 0x464C457F
#define ELF_MAGIC_BE 0x4C467F45

#ifdef __cplusplus
extern "C" {
#endif

enum {
    ELF_BITS_32 = 1,
    ELF_BITS_64 = 2,
};

enum {
    ELF_ENDIAN_LITTLE = 1,
    ELF_ENDIAN_BIG = 2,
};

typedef struct {
    uint32_t magic;
    uint8_t bits;
    uint8_t endianness;
    uint8_t version;
    uint8_t osabi;
    uint8_t abiversion;
    uint8_t padding[7];
} __attribute__((packed)) elf_ident_t;

typedef struct {
    elf_ident_t ident;
    uint16_t type;
    uint16_t machine;
    uint32_t version;
    uint32_t entry;
    uint32_t phoff;
    uint32_t shoff;
    uint32_t flags;
    uint16_t ehsize;
    uint16_t phentsize;
    uint16_t phnum;
    uint16_t shentsize;
    uint16_t shnum;
    uint16_t shstrndx;
} __attribute__((packed)) elf32_header_t;

typedef struct {
    volatile elf_ident_t ident;
    uint16_t type;
    uint16_t machine;
    uint32_t version;
    uint64_t entry;
    uint64_t phoff;
    uint64_t shoff;
    uint32_t flags;
    uint16_t ehsize;
    uint16_t phentsize;
    uint16_t phnum;
    uint16_t shentsize;
    uint16_t shnum;
    uint16_t shstrndx;
} __attribute__((packed)) elf64_header_t;

typedef struct {
    uint32_t type;
    uint32_t offset;
    uint32_t vaddr;
    uint32_t paddr;
    uint32_t filesz;
    uint32_t memsz;
    uint32_t flags;
    uint32_t align;
} __attribute__((packed)) elf32_program_header_t;

typedef struct {
    uint32_t type;
    uint32_t flags;
    uint64_t offset;
    uint64_t vaddr;
    uint64_t paddr;
    uint64_t filesz;
    uint64_t memsz;
    uint64_t align;
} __attribute__((packed)) elf64_program_header_t;

typedef struct {
    uint32_t type;
    uint32_t flags;
    uint32_t addr;
    uint32_t offset;
    uint32_t size;
    uint32_t link;
    uint32_t info;
    uint32_t addralign;
    uint32_t entsize;
} __attribute__((packed)) elf32_section_header_t;

typedef struct {
    uint32_t type;
    uint64_t flags;
    uint64_t addr;
    uint64_t offset;
    uint64_t size;
    uint32_t link;
    uint32_t info;
    uint64_t addralign;
    uint64_t entsize;
} __attribute__((packed)) elf64_section_header_t;

typedef struct {
    bool is_le;
    bool is_64;
    union {
	volatile elf32_header_t* eh32;
	volatile elf64_header_t* eh64;
    };

    union {
	volatile elf32_program_header_t* ph32;
	volatile elf64_program_header_t* ph64;
    };

    union {
	volatile elf32_section_header_t* sh32;
	volatile elf64_section_header_t* sh64;
    };

    uint8_t* data;
} elf_t;

bool elf_load(uint8_t* data, elf_t* out);

#ifdef __cplusplus
}
#endif

#endif
