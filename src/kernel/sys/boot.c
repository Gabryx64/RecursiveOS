#include<stdint.h>
#include<stddef.h>
#include<stivale2.h>
#include"sys.h"
#include"GDT/GDT.h"
#include"IDT/IDT.h"
#include"PMM/PMM.h"

static uint8_t stack[4096];

static struct stivale2_header_tag_framebuffer framebuffer_hdr_tag =
{
    .tag =
    {
        .identifier = STIVALE2_HEADER_TAG_FRAMEBUFFER_ID,
        .next = 0
    },

    .framebuffer_width  = 0,
    .framebuffer_height = 0,
    .framebuffer_bpp    = 0
};

__attribute__((section(".stivale2hdr"), used))
static struct stivale2_header stivale_hdr =
{
    .entry_point = 0,
    .stack = (uintptr_t)stack + sizeof(stack),
    .flags = 0,
    .tags = (uintptr_t)&framebuffer_hdr_tag
};

void *stivale2_get_tag(struct stivale2_struct *stivale2_struct, uint64_t id) {
    struct stivale2_tag *current_tag = (void *)stivale2_struct->tags;
    for (;;)
    {
        if (current_tag == NULL) {
            return NULL;
        }

        if (current_tag->identifier == id) {
            return current_tag;
        }

        current_tag = (void *)current_tag->next;
    }
}

struct stivale2_struct_tag_framebuffer* fb_tag;
volatile uint32_t* fb;
extern void kmain(void);

void _start(struct stivale2_struct *stivale2_struct)
{
    GDT_init();

    fb_tag = stivale2_get_tag(stivale2_struct, STIVALE2_STRUCT_TAG_FRAMEBUFFER_ID);

    if (fb_tag == NULL)
    {
        for (;;)
        {
            asm("hlt");
        }
    }

    fb = (uint32_t*)fb_tag->framebuffer_addr;

    IDT_init();
    // PMM_init(); // TODO: fix PMM

    kmain();

    for(;;)
    {
        asm("hlt");
    }
}
