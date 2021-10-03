#include"panic.h"
#include"io.h"

void __panic(char* file, const char* function, int line, char* msg)
{
  clearterm();
  printf("Unhandled Exception:%s:%s:%d: `%s`", file, function, line, msg);

  asm volatile("cli");
  while(1)
    ;
}
