#include"liballoc.h"
#include"sys/memory/PMM.h"

int liballoc_lock()
{
    // TODO: Implement an actual thread lock when concurrency is implemented
    return 0;
}

int liballoc_unlock()
{
    // TODO: Implement an actual thread unlock when concurrency is implemented
    return 0;
}

void* liballoc_alloc(size_t pages)
{
    return PMM_alloc(pages);
}

int liballoc_free(void* ptr, size_t pages)
{
    return PMM_free(ptr, pages);
}
