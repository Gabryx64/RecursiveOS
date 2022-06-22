#ifndef LIBK_MATHUTILS_H
#define LIBK_MATHUTILS_H 1
#include<stdint.h>

#define MAX(x, y) (x > y ? x : y)
#define MIN(x, y) (x < y ? x : y)

#define abs(x)   (x < 0 ? -x : x)

#define DIV_RNDUP(x, y) ((x % y) ? (x / y + 1) : (x / y))

#endif
