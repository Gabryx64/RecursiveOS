#ifndef PMM_H
#define PMM_H 1
#include "sys/sys.h"
#include <limine.h>
#include <stddef.h>

#define PAGE_SIZE 4096

#ifdef __cplusplus
extern "C" {
#endif

void* PMM_alloc(size_t pages);
int PMM_free(void* ptr, size_t pages);
void PMM_init(struct limine_memmap_response* memory_map);

#ifdef __cplusplus
}
#endif

#endif