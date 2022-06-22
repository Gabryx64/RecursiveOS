#include"PMM.h"
#include"mathutils.h"
#include"log.h"
#include"str.h"

#include<stdint.h>

static uint64_t* stack;
static size_t stack_idx = 0;
static size_t stack_size;

void* PMM_alloc(size_t pages)
{
  if(pages == 0)
    return NULL;

  for(size_t i = stack_idx; i < stack_size; i++)
  {
    size_t consecutive = 1;
    uint64_t ptr = stack[i];

    size_t indices[pages];
    indices[0] = i;

    for(size_t j = i; j < stack_size; j++)
    {
      if(consecutive == pages)
        break;

      if(stack[j] == ptr + consecutive * PAGE_SIZE)
        indices[consecutive++] = j;
    }

    for(size_t j = stack_idx; j < i; j++)
    {
      if(consecutive == pages)
        break;

      if(stack[j] == ptr + consecutive * PAGE_SIZE)
        indices[consecutive++] = j;
    }

    stack_idx += pages;

    if(consecutive == pages)
    {
      for(size_t j = 0; j < pages; j++)
      {
        for(size_t k = indices[j]; k > 0; k--)
          stack[k] = stack[k - 1];
      }

      return (void*)ptr;
    }
  }

  return NULL;
}

void PMM_free(void* ptr, size_t pages)
{
  if(pages == 0 || !ptr)
    return;
  
  for(size_t i = 0; i < pages; i++)
  {
    stack[--stack_idx] = (uint64_t)ptr + pages * PAGE_SIZE;
  }
}

void PMM_init(struct stivale2_struct_tag_memmap* memory_map)
{
  log$(INFO, "Initializing PMM...");
  size_t needed = 0;
  for(size_t i = 0; i < memory_map->entries; i++)
  {
    if(memory_map->memmap[i].type & (STIVALE2_MMAP_USABLE | STIVALE2_MMAP_BOOTLOADER_RECLAIMABLE))
    {
      needed += memory_map->memmap[i].length;
    }
  }

  size_t pages = DIV_RNDUP(needed, PAGE_SIZE);
  size_t stack_host = 0;
  for(size_t i = 0; i < memory_map->entries; i++)
  {
    if(memory_map->memmap[i].type & (STIVALE2_MMAP_USABLE | STIVALE2_MMAP_BOOTLOADER_RECLAIMABLE))
    {
      if(memory_map->memmap[i].length >= pages * 8)
      {
        stack = (uint64_t*)memory_map->memmap[i].base;
        stack_size = pages;
        stack_host = i;
        break;
      }
    }
  }

  for(size_t i = 0; i < memory_map->entries; i++)
  {
    if(memory_map->memmap[i].type & (STIVALE2_MMAP_USABLE | STIVALE2_MMAP_BOOTLOADER_RECLAIMABLE))
    {
      if(i == stack_host)
      {
        for(size_t j = 0; j < memory_map->memmap[i].length; j += PAGE_SIZE)
        {
          stack[stack_idx++] = memory_map->memmap[i].base + j;
        }
      }
      else
      {
        size_t start = ((pages * 8 + PAGE_SIZE - 1) / PAGE_SIZE) * PAGE_SIZE;
        for(size_t j = start; j < memory_map->memmap[i].length; j += PAGE_SIZE)
        {
          stack[stack_idx++] = memory_map->memmap[i].base + j;
        }
      }
    }
  }
  stack_idx = 0;

  log$(INFO, "PMM initialized!");
}
