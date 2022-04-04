#include"PMM.h"
#include"log.h"
#include"sys/panic.h"

#define BIT_SET(BIT, MAP) (MAP[(BIT) / 8] |= (1 << ((BIT) % 8)))
#define BIT_CLEAR(BIT, MAP) (MAP[(BIT) / 8] &= ~(1 << ((BIT) % 8)))
#define BIT_TEST(BIT, MAP) ((MAP[(BIT) / 8] >> ((BIT) % 8)) & 1)

#define ALIGN_UP(NUM, WHAT) (((NUM) + WHAT - 1) & ~(WHAT - 1))
#define ALIGN_DOWN(NUM, WHAT) ((NUM) & ~(WHAT - 1))
#define DIV_ROUNDUP(A, B) ({(A + (B - 1)) / B;})

void clear_page(void* addr)
{
  BIT_CLEAR((uint64_t)addr / PAGE_SIZE, bitmap.data);
  usable_pages++;
}

void set_page(void* addr)
{
  BIT_SET((uint64_t)addr / PAGE_SIZE, bitmap.data);
  usable_pages--;
}

void set_pages(void* addr, size_t page_count)
{
  for(size_t i = 0; i < page_count; i++)
    set_page((void *)(addr + (i * PAGE_SIZE)));
}

void PMM_free(void* addr, size_t pages)
{
  for(size_t i = 0; i < pages; i++)
    clear_page((void *)(addr + (i * PAGE_SIZE)));
}

void* PMM_alloc(size_t pages)
{
	if(pages > bitmap.size)
  {
    log$(PANIC, "Allocation of {} bytes is too big", bitmap.size);
    return NULL;
  }

  for(size_t i = 0; i < highest_page / PAGE_SIZE; i++)
  {
    for(size_t j = 0; j < pages; j++)
    {
      if(BIT_TEST(i, bitmap.data))
      {
        break;
      }
      else if(j == pages - 1)
      {
        void *ret = (void*)(i * PAGE_SIZE);
        set_pages(ret, pages);

        return ret;
      }
    }
  }

  return NULL;
}

void* PMM_alloc0(size_t pages)
{
	void* ret = PMM_alloc(pages);
  memset(ret + MMAP_IO_BASE, 0, pages * PAGE_SIZE);

  return ret;
}

void PMM_init(volatile struct stivale2_struct_tag_memmap* memory_map)
{
	uintptr_t top = 0;

  for(size_t i = 0; i < memory_map->entries; i++)
  {
    volatile struct stivale2_mmap_entry* entry = &memory_map->memmap[i];

    if(entry->type != STIVALE2_MMAP_USABLE &&
			entry->type != STIVALE2_MMAP_BOOTLOADER_RECLAIMABLE &&
			entry->type != STIVALE2_MMAP_KERNEL_AND_MODULES)
      continue;

    top = entry->base + entry->length;
    if(top > highest_page)
      highest_page = top;
  }

  size_t bitmap_size = ALIGN_UP(ALIGN_DOWN(highest_page, PAGE_SIZE) / PAGE_SIZE / 8, PAGE_SIZE);
	assert(bitmap_size != 0, "bitmap_size == 0");

  bitmap.size = bitmap_size;

  for(size_t i = 0; i < memory_map->entries; i++)
  {
    volatile struct stivale2_mmap_entry* entry = &memory_map->memmap[i];
    if(entry->type == STIVALE2_MMAP_USABLE && entry->length >= bitmap_size)
    {
      bitmap.data = (uint8_t*)(entry->base + MMAP_IO_BASE);
      entry->base += bitmap_size;
      entry->length -= bitmap_size;
      break;
    }
  }

  memset(bitmap.data, 0xff, bitmap.size);
  for(size_t i = 0; i < memory_map->entries; i++)
  {
    if(memory_map->memmap[i].type == STIVALE2_MMAP_USABLE)
      PMM_free((void*)memory_map->memmap[i].base, memory_map->memmap[i].length / PAGE_SIZE);
  }
	log$(INFO, "PMM initialized");
}
