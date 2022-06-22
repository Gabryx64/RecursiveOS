#include"log.h"
#include"str.h"
#include"portio.h"

template<>
void log$<>(bool x)
{
	serial_writestr(x ? "true" : "false");
}

template<>
void log$<>(long x)
{
	char buf[21];
	ltoa(buf, x);
	serial_writestr(buf);
}

template<>
void log$<>(unsigned long x)
{
	char buf[21];
	ultoa(buf, x);
	serial_writestr(buf);
}

template<>
void log$<>(const char* x)
{
	serial_writestr(x);
}

template<typename... Types>
void log$(bool x, Types... xs)
{
	serial_writestr(x ? "true" : "false");
}

template<typename... Types>
void log$(long x, Types... xs)
{
	char buf[21];
	ltoa(buf, x);
	serial_writestr(buf);
}

template<typename... Types>
void log$(unsigned long x, Types... xs)
{
	char buf[21];
	ultoa(buf, x);
	serial_writestr(buf);
}

template<typename... Types>
void log$(const char* x, Types... xs)
{
	serial_writestr(x);
}
