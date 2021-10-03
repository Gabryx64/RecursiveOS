#include"mathutils.h"

long double pow(long double base, long double power)
{
  double ret = 1;

  for(int i = 0; i < power; i++)
    ret *= base;

  return ret;
}

long double log(long double n)
{
  return (n > 1) ? 1 + log(n / 2) : 0;
}
