#include"alloc.h"
#include"mathutils.h"
#include"str.h"
#include"sys/memory/PMM.h"
#include"log.h"

#ifdef __clang__
#define NOOPT __attribute__((optnone))
#else
#define NOOPT __attribute__((optimize("O0")))
#endif

slab_t* NOOPT small_slab_create(size_t size, size_t align, slab_t* prev, slab_t* next)
{
	void* mem = PMM_alloc(1);
	slab_t* ret = mem + 4096 - sizeof(slab_t);
	ret->prev = prev ? prev : ret;
	ret->next = next ? next : ret;
	ret->firstbuf = (bufctl_t*)mem;
	
	size_t buffers = (4096 - sizeof(slab_t)) / (sizeof(bufctl_t) + align);
	bufctl_t* last = (bufctl_t*)mem;
	for(size_t i = 0; i < buffers; i++)
	{
		bufctl_t* buf = (bufctl_t*)(mem + (sizeof(bufctl_t) + align) * i);
		buf->free = true;
		buf->prev = last;
		buf->prev->next = buf;
		buf->next = (bufctl_t*)mem;
		buf->mem = buf + sizeof(bufctl_t);
		((bufctl_t*)mem)->prev = buf;
		last = buf;
	}
	
	return ret;
}

void NOOPT small_slab_destroy(slab_t* slab)
{
	slab->next->prev = slab->prev;
	slab->prev->next = slab->next;
	PMM_free(slab->firstbuf, 1);
}

void* NOOPT small_slab_alloc(slab_t* slab, void* source, size_t size, size_t align, slab_t* first_slab, slab_t** free_slab)
{
	bufctl_t* first = slab->firstbuf;
	bufctl_t* curr = first;
	do
	{
		if(curr->free)
		{
			*free_slab = slab;
			memcpy(curr->mem, source, size);
			return curr->mem;
		}
		curr = curr->next;
	} while(curr != first);

	if(slab->next == first_slab)
	{
		slab_t* newslab = small_slab_create(size, align, slab, first_slab);
		first_slab->prev = newslab;
		slab->next = newslab;
	}

	return small_slab_alloc(slab->next, source, size, align, first_slab, free_slab);
}

void NOOPT small_slab_free(void* ptr)
{
	bufctl_t* buf = (bufctl_t*)ptr - sizeof(bufctl_t);
	buf->free = true;
}

slab_t* NOOPT large_slab_create(size_t size, size_t align, slab_t* prev, slab_t* next)
{
	void* mem = PMM_alloc(1);
	slab_t* ret = mem + 4096 - sizeof(slab_t);
	ret->prev = prev ? prev : ret;
	ret->next = next ? next : ret;
	ret->firstbuf = (bufctl_t*)mem;
	
	size_t buffers = (4096 - sizeof(slab_t)) / sizeof(bufctl_t);
	bufctl_t* last = (bufctl_t*)mem;
	for(size_t i = 0; i < buffers; i++)
	{
		bufctl_t* buf = (bufctl_t*)(mem + sizeof(bufctl_t) * i);
		buf->free = true;
		buf->prev = last;
		buf->prev->next = buf;
		buf->next = (bufctl_t*)mem;
		((bufctl_t*)mem)->prev = buf;
		buf->mem = PMM_alloc(DIV_RNDUP(size + sizeof(bufctl_t*), PAGE_SIZE)) + sizeof(bufctl_t*);

		last = buf;
	}
	
	return ret;
}

void NOOPT large_slab_destroy(size_t size, slab_t* slab)
{
	slab->next->prev = slab->prev;
	slab->prev->next = slab->next;
	bufctl_t* first = slab->firstbuf;
	bufctl_t* curr = first;
	do
		PMM_free(curr->mem - sizeof(bufctl_t*), DIV_RNDUP(size + sizeof(bufctl_t*), PAGE_SIZE));
	while(curr != first);

	PMM_free(slab->firstbuf, 1);
}

void* NOOPT large_slab_alloc(slab_t* slab, void* source, size_t size, size_t align, slab_t* first_slab, slab_t** free_slab)
{
	bufctl_t* first = slab->firstbuf;
	bufctl_t* curr = first;
	do
	{
		if(curr->free)
		{
			*free_slab = slab;;
			memcpy(curr->mem, source, size);
			return curr->mem;
		}
		curr = curr->next;
	} while(curr != first);

	if(slab->next == first_slab)
	{
		slab_t* newslab = large_slab_create(size, align, slab, first_slab);
		first_slab->prev = newslab;
		slab->next = newslab;
	}

	return large_slab_alloc(slab->next, source, size, align, first_slab, free_slab);
}

void NOOPT large_slab_free(void* ptr)
{
	bufctl_t* buf = *((bufctl_t**)ptr - sizeof(bufctl_t*));
	buf->free = true;
}


cache_t* cache_create(size_t size, size_t align, void (*constructor)(void* ptr, size_t size), void (*mutator)(void* ptr, size_t size), void (*destructor)(void* ptr, size_t size))
{
	alloc_lock();

	cache_t* ret = PMM_alloc(DIV_RNDUP(sizeof(cache_t) + size, 4096));
	ret->size = size;
	ret->align = align < size ? size : align;
	ret->large = align >= (PAGE_SIZE / 8);
	ret->slabs = (ret->large ? large_slab_create : small_slab_create)(size, align, NULL, NULL);
	ret->mutatotor = mutator;
	ret->destructor = destructor;
	constructor(ret->source = ret + sizeof(cache_t), size);

	alloc_unlock();

	return ret;
}

void cache_destroy(cache_t* cache)
{
	alloc_lock();

	slab_t* first = cache->slabs;
	cache->destructor(cache->source, cache->size);
	slab_t* curr = cache->slabs;
	do
	{
		slab_t* slab = curr;
		curr = curr->next;
		cache->large ? large_slab_destroy(cache->size, slab) : small_slab_destroy(slab);
	} while(curr != first);
	PMM_free(cache, 1);

	alloc_unlock();
}

void* cache_alloc(cache_t* cache)
{
	alloc_lock();

	void* ret = (cache->large ? large_slab_alloc : small_slab_alloc)(cache->slabs, cache->source, cache->size, cache->align, cache->slabs, &cache->slabs);
	cache->mutatotor(ret, cache->size);

	alloc_unlock();

	return ret;
}

void cache_free(cache_t* cache, void* ptr)
{
	alloc_lock();

	(cache->large ? large_slab_free : small_slab_free)(ptr);

	alloc_unlock();
}
