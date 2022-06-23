#ifndef LIBK_ALLOC_H
#define LIBK_ALLOC_H 1
#include<stdbool.h>
#include<stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct BUFCTL_S
{
	struct SLAB_S* backptr;
	struct BUFCTL_S* prev;
	struct BUFCTL_S* next;
	void* mem;
	bool free;
} __attribute__((packed)) bufctl_t;

typedef struct SLAB_S
{
	struct SLAB_S* prev;
	struct SLAB_S* next;
	bufctl_t* firstbuf;
} __attribute__((packed)) slab_t;

typedef struct CACHE_S
{
	bool large;
	slab_t* slabs;
	size_t size;
	size_t align;
	void* source;
	void (*mutatotor)(void* ptr, size_t size);
	void (*destructor)(void* ptr, size_t size);
} cache_t;

cache_t* cache_create(size_t size, size_t align, void (*constructor)(void* ptr, size_t size), void (*mutator)(void* ptr, size_t size), void (*destructor)(void* ptr, size_t size));
void cache_destroy(cache_t* cache);
void* cache_alloc(cache_t* cache);
void cache_free(cache_t* cache, void* ptr);

inline void __alloc_noop__(void* ptr, size_t size){ (void)ptr; (void)size; }
#define NODESTRUCT  __alloc_noop__
#define NOCONSTRUCT __alloc_noop__
#define NOMUTATE    __alloc_noop__

// TODO: Make it do something when concurrency is implemented
inline void alloc_lock()   {}
inline void alloc_unlock() {}

#ifdef __cplusplus
}
#endif

#endif
