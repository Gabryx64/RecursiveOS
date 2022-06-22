#ifndef LIBK_LOG_H
#define LIBK_LOG_H 1
#include<stdbool.h>

#include"map_macro.h"

#ifndef __cplusplus

typedef enum
{
	ARG_TYPE_BOOL,
	ARG_TYPE_CHAR,
	ARG_TYPE_BYTE,
	ARG_TYPE_SHORT,
	ARG_TYPE_USHORT,
	ARG_TYPE_INT,
	ARG_TYPE_UINT,
	ARG_TYPE_LONG,
	ARG_TYPE_ULONG,
	ARG_TYPE_CHARPTR,
	ARG_TYPE_VOIDPTR,
} ArgType;

typedef struct
{
	ArgType type;
	union
	{
		bool b;
		char c;
		unsigned char uc;
		short s;
		unsigned short us;
		int i;
		unsigned u;
		long l;
		unsigned long ul;
		const char* cp;
		void* p;
	} val;
} Arg;

inline Arg arg_bool(bool b)
{
	Arg arg;
	arg.type = ARG_TYPE_BOOL;
	arg.val.b = b;
	return arg;
}

inline Arg arg_char(char c)
{
	Arg arg;
	arg.type = ARG_TYPE_CHAR;
	arg.val.c = c;
	return arg;
}

inline Arg arg_byte(unsigned char uc)
{
	Arg arg;
	arg.type = ARG_TYPE_BYTE;
	arg.val.uc = uc;
	return arg;
}

inline Arg arg_short(short s)
{
	Arg arg;
	arg.type = ARG_TYPE_SHORT;
	arg.val.s = s;
	return arg;
}

inline Arg arg_ushort(unsigned short us)
{
	Arg arg;
	arg.type = ARG_TYPE_USHORT;
	arg.val.us = us;
	return arg;
}

inline Arg arg_int(int i)
{
	Arg arg;
	arg.type = ARG_TYPE_INT;
	arg.val.i = i;
	return arg;
}

inline Arg arg_uint(unsigned u)
{
	Arg arg;
	arg.type = ARG_TYPE_UINT;
	arg.val.u = u;
	return arg;
}

inline Arg arg_long(long l)
{
	Arg arg;
	arg.type = ARG_TYPE_LONG;
	arg.val.l = l;
	return arg;
}

inline Arg arg_ulong(unsigned long ul)
{
	Arg arg;
	arg.type = ARG_TYPE_ULONG;
	arg.val.ul = ul;
	return arg;
}

inline Arg arg_charptr(const char* cp)
{
	Arg arg;
	arg.type = ARG_TYPE_CHARPTR;
	arg.val.cp = cp;
	return arg;
}

inline Arg arg_voidptr(void* p)
{
	Arg arg;
	arg.type = ARG_TYPE_VOIDPTR;
	arg.val.p = p;
	return arg;
}

#define ARG(x) _Generic((x),                                         \
          bool: arg_bool,               unsigned char: arg_byte,    \
           char: arg_char,                 signed char: arg_char,    \
      short int: arg_short,         unsigned short int: arg_ushort,  \
            int: arg_int,                 unsigned int: arg_uint,    \
       long int: arg_long,           unsigned long int: arg_ulong,   \
          char*: arg_charptr,                    void*: arg_voidptr, \
 	  const bool: arg_bool,         const unsigned char: arg_byte,    \
     const char: arg_char,           const signed char: arg_char,    \
const short int: arg_short,   const unsigned short int: arg_ushort,  \
      const int: arg_int,           const unsigned int: arg_uint,    \
 const long int: arg_long,     const unsigned long int: arg_ulong,   \
    const char*: arg_charptr,              const void*: arg_voidptr, \
		    default: arg_voidptr)(x),

#define ARGS_(...) (Arg*)(Arg[]){}
#define ARGS_N(...) (Arg*)(Arg[]){ MAP_MACRO(ARG, ##__VA_ARGS__) }

#define log$(type, fmt, ...) _log(__FILE__ " [" #type "] " fmt "\n", ARGS_##__VA_OPT__(N)(__VA_ARGS__))

void _log(const char* fmt, Arg args[]);

#endif

#endif
