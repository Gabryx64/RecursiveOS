#ifndef LIBK_GABALLOC_EXT_H
#define LIBK_GABALLOC_EXT_H 1

// Includes for defines
#include "str.h"
#include "sys/memory/PMM.h"

// Defines
#define GABALLOC_PAGE_SIZE PAGE_SIZE
#define GABALLOC_ALLOC PMM_alloc
#define GABALLOC_FREE PMM_free
#define GABALLOC_MEMCPY memcpy
#define GABALLOC_LOCK alloc_lock
#define GABALLOC_UNLOCK alloc_unlock

#ifdef __cplusplus
extern "C" {
#endif

// TODO: Make it do something when concurrency is implemented
inline void alloc_lock() {}
inline void alloc_unlock() {}

#ifdef __cplusplus
}
#endif

#endif
