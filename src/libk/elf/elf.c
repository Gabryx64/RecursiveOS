#include"elf.h"
#include"log.h"
#include<stddef.h>

bool elf_load(uint8_t* data, elf_t* out)
{
	volatile elf_ident_t* ident = (elf_ident_t*)data;
	bool is_le;
	switch(ident->endianness)
	{
		case ELF_ENDIAN_LITTLE:
			is_le = true;
			break;

		case ELF_ENDIAN_BIG:
			is_le = false;
			break;

		default:
			return false;
	}

	if(ident->magic != (is_le ? ELF_MAGIC_LE : ELF_MAGIC_BE))
		return false;

	out->is_le = is_le;
	switch(ident->bits)
	{
		case ELF_BITS_32:
			out->is_64 = false;
			out->eh32 = (volatile elf32_header_t*)data;
			out->ph32 = (volatile elf32_program_header_t*)(data + out->eh32->phoff);
			out->sh32 = (volatile elf32_section_header_t*)(data + out->eh32->shoff);
			out->data = data;
			break;

		case ELF_BITS_64:
			out->is_64 = true;
			out->eh64 = (volatile elf64_header_t*)data;
			out->ph64 = (volatile elf64_program_header_t*)(data + out->eh64->phoff);
			out->sh64 = (volatile elf64_section_header_t*)(data + out->eh64->shoff);
			out->data = data;
			break;

		default:
			return false;
	};

	return true;
};

