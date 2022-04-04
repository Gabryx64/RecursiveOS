#ifndef LIBK_PMM_H
#define LIBK_PMM_H 1
#include"sys/memory/PMM.h"

typedef struct
{
  uint64_t pages;
  uint64_t size;
} heap_data;

void* malloc(size_t size);
void free(void* ptr);

#endif
