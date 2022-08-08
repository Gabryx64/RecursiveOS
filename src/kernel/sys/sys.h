#include "limine.h"
#ifndef SYS_H
#define SYS_H 1
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

extern struct limine_framebuffer* _fb;
extern volatile uint32_t* fb;

#ifdef __cplusplus
}
#endif

#endif
