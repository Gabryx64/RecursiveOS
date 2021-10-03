#include"io.h"

int current_col = 0, current_row = 0;

void outb(uint16_t port, uint8_t val)
{
  asm volatile ("outb %0, %1"
				  :
				  : "a"(val), "Nd"(port) );
}

uint8_t inb(uint16_t port)
{
  uint8_t ret;
  asm volatile ("inb %1, %0"
          : "=a"(ret)
          : "Nd"(port) );
  return ret;
}

void outl(uint16_t port, uint32_t val)
{
  asm volatile ("out %0, %1"
				  :
				  : "a"(val), "d"(port) );
}

uint32_t inl(uint16_t port)
{
  uint32_t ret;
  asm volatile ("in %1, %0"
          : "=a"(ret)
          : "d"(port) );
  return ret;
}

void outw(uint16_t port, uint16_t val)
{
  asm volatile ("outw %0, %1"
				  :
				  : "a"(val), "d"(port) );
}

void clearterm()
{
  clearscreen(bg_col);
  current_col = 0;
  current_row = 0;
}

int snapped_putch(wchar_t ch, int column, int row, Color fg, Color bg)
{
  int x = column * 8, y = row * 8;

  if(x >= 640 || y >= 480)
    return -1;

  putch(ch, x, y, fg, bg);

  return ch;
}

bool reading_escape_code = false;

int putchar(wchar_t ch)
{
  int ret = ch;

  if(ch >= ' ')
	{
    ret = snapped_putch(ch, current_col, current_row, fg_col, bg_col);
    
    if(ret == -1)
      return ret;
      
    current_col++;
  }
	else
  {
		switch(ch)
		{
			case L'\a':
    	{
				// Implement "Bell"
    	} break;

			case L'\b':
    	{
				current_col--;
				snapped_putch(L' ', current_col, current_row, fg_col, bg_col);
				current_col--;
    	} break;

			case L'\t':
    	{
				current_col += 4;
    	} break;

			case L'\f':
			{
				clearterm();
			} break;

			case L'\v':
			{
				current_row++;
    	} break;

			case L'\n':
    	{
				current_row++;
				current_col = 0;
    	} break;

			case L'\r':
    	{
				current_col = 0;
    	} break;

			case L'\033':
			{

			} break;
		}
  }

  while(current_col >= 640)
  {
    current_col -= 640;
    current_row++;
  }

  if(current_row >= 480)
    return -1;

  return ret;
}

static uint8_t count_ones(uint8_t data)
{
	uint8_t ones = 0;
	for(size_t j = 0; (data >> (7 - j)) & 1 && j < 8; j++)
		ones++;

	return ones;
}
 
static bool print(const char* data, size_t length)
{
	for(size_t i = 0; i < length; i++)
	{
		uint8_t ones = count_ones((uint8_t)data[i]);

		wchar_t ch;
		switch(ones)
		{
			case 0:
			{
				ch = (wchar_t)data[i];
			} break;

			case 2:
			{
				if(i + 1 >= length || count_ones((uint8_t)data[i + 1] != 1))
					return false;

				ch = ((wchar_t)data[i] & 0b00011111) << 6;
				ch |= (wchar_t)data[i + 1] & 0b00111111;

				i++;
			} break;

			case 3:
			{
				if(i + 2 >= length || count_ones((uint8_t)data[i + 1] != 1) ||
					 count_ones((uint8_t)data[i + 2] != 1))
					return false;

				ch = ((wchar_t)data[i] & 0b00001111) << 12;
				ch |= ((wchar_t)data[i + 1] & 0b00111111) << 6;
				ch |= (wchar_t)data[i + 2] & 0b00111111;

				i += 2;
			} break;

			case 4:
			{
				if(i + 3 >= length || count_ones((uint8_t)data[i + 1] != 1) ||
					 count_ones((uint8_t)data[i + 2] != 1) || count_ones((uint8_t)data[i + 3] != 1))
					return false;

				ch = ((wchar_t)data[i] & 0b00000111) << 18;
				ch |= ((wchar_t)data[i + 1] & 0b00111111) << 12;
				ch |= ((wchar_t)data[i + 2] & 0b00111111) << 6;
				ch |= (wchar_t)data[i + 3] & 0b00111111;

				i += 3;
			} break;

			default: return false;
		}

		if(putchar(ch) == EOF)
			return false;
	}

	return true;
}


int printf(const char* restrict format, ...)
{
	va_list parameters;
	va_start(parameters, format);
 
	int written = 0;
 
	while(*format != '\0')
  {
		size_t maxrem = INT_MAX - written;
 
		if(format[0] != '%' || format[1] == '%')
    {
			if(format[0] == '%')
				format++;

			size_t amount = 1;

			while (format[amount] && format[amount] != '%')
				amount++;

			if(maxrem < amount)
      {
				return -1;
			}

			if(!print(format, amount))
				return -1;

			format += amount;
			written += amount;

			continue;
		}
 
		const char* format_begun_at = format++;
 
		if(*format == 'c')
    {
			format++;
			char c = (char)va_arg(parameters, int);

			if(!maxrem)
      {
				return -1;
			}

			if(!print((char*)&c, sizeof(c)))
				return -1;
			written++;
		}
    else if(*format == 's')
    {
			format++;

			const char* str = va_arg(parameters, const char*);
			size_t len = strlen(str);

			if(maxrem < len)
      {
				return -1;
			}

			if(!print((char*)str, len))
				return -1;

			written += len;
		}
    else
    {
			format = format_begun_at;
			size_t len = strlen(format);

			if(maxrem < len)
      {
				return -1;
			}

			if(!print(format, len))
				return -1;

			written += len;
			format += len;
		}
	}
 
	va_end(parameters);
	return written;
}
