#ifndef LIBK_EMBED_H
#define LIBK_EMBED_H 1
#include"str.h"

#define EMBED(id, embed_type, embed_name, file)                                \
  __asm__(                                                                     \
  	".section .rodata\n"                                                       \
    ".global __incbin_" to_string(id) "__\n"                                   \
    ".balign 16\n"                                                             \
    "__incbin_" to_string(id) "__:\n"                                          \
    ".incbin \"" file "\"\n"                                                   \
		".byte 0\n"                                              \
  );                                                                           \
  extern const __attribute__((aligned(16))) void* __incbin_ ## id ## __;       \
	embed_type embed_name = (embed_type)(&__incbin_ ## id ## __)

#define EMBED_BIN(id, embed_type, embed_name, file)                            \
  __asm__(                                                                     \
  	".section .rodata\n"                                                       \
    ".global __incbin_" to_string(id) "__\n"                                   \
    ".balign 16\n"                                                             \
    "__incbin_" to_string(id) "__:\n"                                          \
    ".incbin \"" file "\"\n"                                                   \
  );                                                                           \
  extern const __attribute__((aligned(16))) void* __incbin_ ## id ## __;       \
	embed_type embed_name = (embed_type)(&__incbin_ ## id ## __)

#endif
