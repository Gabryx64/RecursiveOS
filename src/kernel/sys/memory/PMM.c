#include "PMM.h"
#include "limine.h"
#include "log.h"
#include "mathutils.h"
#include "str.h"

#include <stdint.h>

static uint64_t* stack;
static size_t stack_idx = 0;
static size_t stack_size;

void* PMM_alloc(size_t pages) {
    if (pages == 0)
	return NULL;

    for (size_t i = stack_idx; i < stack_size; i++) {
	size_t consecutive = 1;
	uint64_t ptr = stack[i];

	size_t indices[pages];
	indices[0] = i;

	for (size_t j = i; j < stack_size; j++) {
	    if (consecutive == pages)
		break;

	    if (stack[j] == ptr + consecutive * PAGE_SIZE)
		indices[consecutive++] = j;
	}

	for (size_t j = stack_idx; j < i; j++) {
	    if (consecutive == pages)
		break;

	    if (stack[j] == ptr + consecutive * PAGE_SIZE)
		indices[consecutive++] = j;
	}

	stack_idx += pages;

	if (consecutive == pages) {
	    for (size_t j = 0; j < pages; j++) {
		for (size_t k = indices[j]; k > 0; k--)
		    stack[k] = stack[k - 1];
	    }

	    return (void*)ptr;
	}
    }

    return NULL;
}

int PMM_free(void* ptr, size_t pages) {
    if (pages == 0 || !ptr)
	return -1;

    for (size_t i = 0; i < pages; i++)
	stack[--stack_idx] = (uint64_t)ptr + pages * PAGE_SIZE;

    return 0;
}

void PMM_init(struct limine_memmap_response* memory_map) {
    log$(INFO, "Initializing PMM...");
    size_t needed = 0;
    for (size_t i = 0; i < memory_map->entry_count; i++) {
	if (memory_map->entries[i]->type == LIMINE_MEMMAP_USABLE ||
	    memory_map->entries[i]->type ==
		LIMINE_MEMMAP_BOOTLOADER_RECLAIMABLE)
	    needed += memory_map->entries[i]->length;
    }

    size_t pages = DIV_RNDUP(needed, PAGE_SIZE);
    size_t stack_host = 0;
    for (size_t i = 0; i < memory_map->entry_count; i++) {
	if (memory_map->entries[i]->type == LIMINE_MEMMAP_USABLE ||
	    memory_map->entries[i]->type ==
		LIMINE_MEMMAP_BOOTLOADER_RECLAIMABLE) {
	    if (memory_map->entries[i]->length >= pages * 8) {
		stack = (uint64_t*)memory_map->entries[i]->base;
		stack_size = pages;
		stack_host = i;
		break;
	    }
	}
    }

    for (size_t i = 0; i < memory_map->entry_count; i++) {
	if (memory_map->entries[i]->type == LIMINE_MEMMAP_USABLE ||
	    memory_map->entries[i]->type ==
		LIMINE_MEMMAP_BOOTLOADER_RECLAIMABLE) {
	    if (i == stack_host) {
		for (size_t j = 0; j < memory_map->entries[i]->length;
		     j += PAGE_SIZE) {
		    stack[stack_idx++] = memory_map->entries[i]->base + j;
		}
	    } else {
		size_t start =
		    ((pages * 8 + PAGE_SIZE - 1) / PAGE_SIZE) * PAGE_SIZE;
		for (size_t j = start; j < memory_map->entries[i]->length;
		     j += PAGE_SIZE) {
		    stack[stack_idx++] = memory_map->entries[i]->base + j;
		}
	    }
	}
    }
    stack_idx = 0;

    if (stack_size * 4 > 1024) {
	size_t mbs = stack_size * 4 / 1024;
	if (mbs > 1024)
	    log$(INFO, "PMM initialized!\n{}.{} GiB available for allocation",
		 mbs / 1024, mbs * 100 / 1024 - (mbs / 1024) * 100);
	else
	    log$(INFO, "PMM initialized!\n{}.{} MiB available for allocation",
		 mbs, stack_size * 400 / 1024 - mbs * 100);
    } else {
	log$(INFO, "PMM initialized!\n{}.00 KiB available for allocation",
	     stack_size * 4);
    }
}
