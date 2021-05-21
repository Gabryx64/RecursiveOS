#ifndef SYS_H
#define SYS_H 1
#include<stdint.h>

extern struct stivale2_struct_tag_framebuffer* fb_tag;
extern volatile uint32_t* fb;

typedef enum
{
    US_QWERTY,
    IT_WINKEYS,
} KB_Layouts;

#endif
