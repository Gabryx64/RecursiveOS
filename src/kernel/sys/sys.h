#ifndef SYS_H
#define SYS_H 1
#include<stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

extern struct stivale2_struct_tag_framebuffer* fb_tag;
extern volatile uint32_t* fb;

#ifdef __cplusplus
}
#endif

#endif
