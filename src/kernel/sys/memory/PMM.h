#ifndef PMM_H
#define PMM_H 1
#include<stddef.h>
#include<stivale2.h>
#include"sys/sys.h"

#define PAGE_SIZE 4096

#ifdef __cplusplus
extern "C" {
#endif

void* PMM_alloc(size_t pages);
void PMM_free(void* ptr, size_t pages);
void PMM_init(struct stivale2_struct_tag_memmap* memory_map);

#ifdef __cplusplus
}
#endif

#endif