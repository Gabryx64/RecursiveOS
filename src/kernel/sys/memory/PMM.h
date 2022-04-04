#ifndef PMM_H
#define PMM_H 1
#include<stddef.h>
#include<stivale2.h>
#include"sys/sys.h"

#define PAGE_SIZE 0x1000
#define MMAP_IO_BASE ((uintptr_t)0xffff800000000000)
#define MMAP_KERNEL_BASE ((uintptr_t)0xffffffff80000000)

void PMM_free(void* addr, size_t pages);
void* PMM_alloc(size_t pages);
void* PMM_alloc0(size_t pages);
void PMM_init(volatile struct stivale2_struct_tag_memmap* memory_map);

#endif