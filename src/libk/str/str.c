#include"str.h"
#include "sys/memory/PMM.h"
#include <bits/stdint-uintn.h>
 
size_t strlen(const char* str)
{
	size_t len = 0;

	while(str[len])
		len++;

	return len;
}

int memcmp(const void* aptr, const void* bptr, size_t size)
{
	const uint8_t* a = (const uint8_t*)aptr;
	const uint8_t* b = (const uint8_t*)bptr;

	for(size_t i = 0; i < size; i++)
  {
		if(a[i] < b[i])
			return -1;
		else if(b[i] < a[i])
			return 1;
	}

	return 0;
}

void* memset(void* bufptr, uint8_t value, size_t size)
{
	uint8_t* buf = (uint8_t*)bufptr;
	for(size_t i = 0; i < size; i++)
		buf[i] = value;

	return bufptr;
}

void* memcpy(void* dstptr, const void* srcptr, size_t size)
{
	uint8_t* dst = (uint8_t*)dstptr;
	const uint8_t* src = (const uint8_t*)srcptr;

	for (size_t i = 0; i < size; i++)
		dst[i] = src[i];

	return dstptr;
}

char* btoa(char buf[4], unsigned char n)
{
	size_t i = 0;
	while(n != 0)
	{
		buf[i++] = (n % 10) + '0';
		n /= 10;
	}
	if (i == 0)
    	buf[i++] = '0';

	buf[i] = '\0';

	for(size_t j = 0; j < i / 2; j++)
	{
		char tmp = buf[j];
		buf[j] = buf[i - j - 1];
		buf[i - j - 1] = tmp;
	}

	return buf;
}

char* stoa(char buf[7], short n)
{
	size_t i = 0;
	while(n != 0)
	{
		buf[i++] = (n % 10) + '0';
		n /= 10;
	}
	if (i == 0)
    	buf[i++] = '0';

	if(n < 0)
	{
		buf[i++] = '-';
		n = -n;
	}

	buf[i] = '\0';

	for(size_t j = 0; j < i / 2; j++)
	{
		char tmp = buf[j];
		buf[j] = buf[i - j - 1];
		buf[i - j - 1] = tmp;
	}

	return buf;
}

char* ustoa(char buf[7], unsigned short n)
{
	size_t i = 0;
	while(n != 0)
	{
		buf[i++] = (n % 10) + '0';
		n /= 10;
	}
	if (i == 0)
    	buf[i++] = '0';

	buf[i] = '\0';

	for(size_t j = 0; j < i / 2; j++)
	{
		char tmp = buf[j];
		buf[j] = buf[i - j - 1];
		buf[i - j - 1] = tmp;
	}

	return buf;
}

char* itoa(char buf[12], int n)
{
	size_t i = 0;
	while(n != 0)
	{
		buf[i++] = (n % 10) + '0';
		n /= 10;
	}
	if (i == 0)
    	buf[i++] = '0';

	if(n < 0)
	{
		buf[i++] = '-';
		n = -n;
	}

	buf[i] = '\0';

	for(size_t j = 0; j < i / 2; j++)
	{
		char tmp = buf[j];
		buf[j] = buf[i - j - 1];
		buf[i - j - 1] = tmp;
	}
	
	return buf;
}

char* utoa(char buf[11], unsigned n)
{
	size_t i = 0;
	while(n != 0)
	{
		buf[i++] = (n % 10) + '0';
		n /= 10;
	}
	if (i == 0)
    	buf[i++] = '0';

	buf[i] = '\0';

	for(size_t j = 0; j < i / 2; j++)
	{
		char tmp = buf[j];
		buf[j] = buf[i - j - 1];
		buf[i - j - 1] = tmp;
	}

	return buf;
}

char* ltoa(char buf[21], long n)
{
	size_t i = 0;
	while(n != 0)
	{
		buf[i++] = (n % 10) + '0';
		n /= 10;
	}
	if (i == 0)
    	buf[i++] = '0';

	if(n < 0)
	{
		buf[i++] = '-';
		n = -n;
	}

	buf[i] = '\0';

	for(size_t j = 0; j < i / 2; j++)
	{
		char tmp = buf[j];
		buf[j] = buf[i - j - 1];
		buf[i - j - 1] = tmp;
	}

	return buf;
}

char* ultoa(char buf[21], unsigned long n)
{
	size_t i = 0;

	while(n != 0)
	{
		buf[i++] = (n % 10) + '0';
		n /= 10;
	}
	if (i == 0)
    	buf[i++] = '0';

	buf[i] = '\0';

	for(size_t j = 0; j < i / 2; j++)
	{
		char tmp = buf[j];
		buf[j] = buf[i - j - 1];
		buf[i - j - 1] = tmp;
	}

	return buf;
}

char* ptrtoa(char buf[17], uintptr_t n)
{
	size_t i = 0;
	while(n != 0)
	{
		uint8_t idx = n % 16;
		if(idx < 10)
			buf[i++] = idx + '0';
		else
			buf[i++] = idx - 10 + 'a';

		n /= 16;
	}
	if (i == 0)
    	buf[i++] = '0';

	buf[i] = '\0';

	for(size_t j = 0; j < i / 2; j++)
	{
		char tmp = buf[j];
		buf[j] = buf[i - j - 1];
		buf[i - j - 1] = tmp;
	}

	return buf;
}
