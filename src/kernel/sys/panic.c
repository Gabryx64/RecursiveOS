#include"panic.h"
#include"io.h"

void panic(char* msg)
{
  clearterm();
  printf("Unhandled Exception: `%s`", msg);

  asm volatile("cli");
  while(1)
    ;
}
