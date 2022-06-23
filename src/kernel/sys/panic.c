#include"panic.h"
#include"log.h"

void panic(const char* msg)
{
  log$(PANIC, "{}", msg);

  __asm__ volatile("cli");
  while(1)
    ;
}
