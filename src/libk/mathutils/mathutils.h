#ifndef LIBK_MATHUTILS_H
#define LIBK_MATHUTILS_H 1
#include<stdint.h>

#define MAX(x, y) (x > y ? x : y)
#define MIN(x, y) (x < y ? x : y)

#define floor(x) ((int64_t)x)

long double pow(long double base, long double power);
long double log(long double n);

#endif
