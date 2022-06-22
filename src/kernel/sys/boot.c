#include<stdint.h>
#include<stddef.h>
#include<limine.h>
#include"sys.h"
#include"GDT.h"
#include"interrupts/IDT.h"
#include"memory/PMM.h"
#include"panic.h"
#include"portio.h"
#include"log.h"

static volatile struct limine_framebuffer_request fb_req =
{
  .id = LIMINE_FRAMEBUFFER_REQUEST,
  .revision = 0
};

static volatile struct limine_memmap_request mmap_req =
{
  .id = LIMINE_MEMMAP_REQUEST,
  .revision = 0
};

volatile uint32_t* fb;
extern void kmain();

Color fg_col, bg_col;

struct limine_framebuffer* _fb;
void _start(void)
{
	serial_init();
  assert(fb_req.response != NULL &&
    fb_req.response->framebuffer_count > 0,
    "Couldn't get a framebuffer");
  assert(mmap_req.response != NULL, "Couldn't get memmap");

  fg_col = UINT_RGB(0xFFFFFF);
  bg_col = UINT_RGB(0x000000);

  GDT_init();
  IDT_init();
  
  PMM_init(mmap_req.response);

  {
    void* ptr = PMM_alloc(1);
    assert(ptr, "Error while initializing PMM");
    //PMM_free(ptr, 1);
  }
  _fb = fb_req.response->framebuffers[0];
  fb = (uint32_t*)_fb->address;

	current_col = 0;
  current_row = 0;

	clearterm();
  kmain();

  while(1)
    __asm__ volatile("hlt");
}
