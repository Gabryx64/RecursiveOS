#include"io.h"

int current_col = 0, current_row = 0;

int snapped_putch(wchar_t ch, int column, int row, Color fg, Color bg)
{
    int x = column * 8, y = row * 8;

    if(x >= 640 || y >= 480)
        return -1;

    putch(ch, x, y, fg, bg);

    return ch;
}

int putchar(wchar_t ch)
{
    int ret = ch;

    if(ch != '\t' && ch != '\n' && ch != '\0')
	{
        ret = snapped_putch(ch, current_col, current_row, fg_col, bg_col);
        
        if(ret == -1)
            return ret;
            
        current_col++;
    }
	else
    {
		if(ch == '\n')
        {
			current_row++;
            current_col = 0;
        }
    }

    if(current_col >= 640)
    {
        current_col = 0;
        current_row++;
    }

    if(current_row >= 480)
    {
        return -1;
    }

    return ret;
}
 
static bool print(const wchar_t* data, size_t length)
{
	for(size_t i = 0; i < length; i++)
		if(putchar(data[i]) == EOF)
			return false;

	return true;
}
 
int printf(const wchar_t* restrict format, ...)
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
 
		const wchar_t* format_begun_at = format++;
 
		if(*format == L'c')
        {
			format++;
			char c = (char)va_arg(parameters, int);

			if(!maxrem)
            {
				return -1;
			}

			if(!print((wchar_t*)&c, sizeof(c)))
				return -1;
			written++;
		}
        else if(*format == L's')
        {
			format++;

			const char* str = va_arg(parameters, const char*);
			size_t len = strlen(str);

			if(maxrem < len)
            {
				return -1;
			}

			if(!print((wchar_t*)str, len))
				return -1;

			written += len;
		}
        else if(*format == L'l')
        {
			format++;

            if(*format == L'c')
            {
		    	format++;
		    	wchar_t c = va_arg(parameters, int);

		    	if(!maxrem)
                {
		    		return -1;
		    	}

		    	if(!print(&c, sizeof(c)))
		    		return -1;
		    	written++;
		    }
            else if(*format == L's')
            {
		    	format++;

		    	const wchar_t* str = va_arg(parameters, const wchar_t*);
		    	size_t len = wstrlen(str);

		    	if(maxrem < len)
                {
		    		return -1;
		    	}

		    	if(!print(str, len))
		    		return -1;

		    	written += len;
		    }
        }
        else
        {
			format = format_begun_at;
			size_t len = wstrlen(format);

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

int puts(wchar_t* str)
{
    return printf(L"%ls\n", str);
}
