#include"log.h"
#include"str.h"
#include"portio.h"

#include<stdint.h>

void _log$(const char* restrict fmt, Arg args[])
{
	size_t len = strlen(fmt);
	size_t args_idx = 0;
	for(size_t i = 0; i < len; i++)
	{
		switch(fmt[i])
		{
			case '{':
				if (fmt[i + 1] == '}')
				{
					i++;
					Arg arg = args[args_idx++];
					switch (arg.type)
					{
						case ARG_TYPE_BOOL:
						{
							serial_writestr(arg.val.b ? "true" : "false");
						} break;

						case ARG_TYPE_CHAR:
						{
							serial_write(arg.val.c);
						} break;

						case ARG_TYPE_BYTE:
						{
							char buf[4];
							btoa(buf, arg.val.uc);
							serial_writestr(buf);
						} break;

						case ARG_TYPE_SHORT:
						{
							char buf[7];
							stoa(buf, arg.val.s);
							serial_writestr(buf);
						} break;

						case ARG_TYPE_USHORT:
						{
							char buf[7];
							ustoa(buf, arg.val.us);
							serial_writestr(buf);
						}	break;

						case ARG_TYPE_INT:
						{
							char buf[12];
							itoa(buf, arg.val.i);
							serial_writestr(buf);
						}	break;

						case ARG_TYPE_UINT:
						{
							char buf[11];
							utoa(buf, arg.val.u);
							serial_writestr(buf);
						}	break;

						case ARG_TYPE_LONG:
						{
							char buf[21];
							ltoa(buf, arg.val.l);
							serial_writestr(buf);
						}	break;

						case ARG_TYPE_ULONG:
						{
							char buf[21];
							ultoa(buf, arg.val.ul);
							serial_writestr(buf);
						}	break;

						case ARG_TYPE_CHARPTR:
						{
							serial_writestr((char*)arg.val.cp);
						}	break;
							
						case ARG_TYPE_VOIDPTR:
						{
							char buf[21];
							ultoa(buf, (uintptr_t)arg.val.p);
							serial_writestr(buf);
						}	break;
					}
				}
				else if (fmt[i + 1] == '{')
				{
					i++;
					serial_write('{');
				}

				break;

			default:
				serial_write(fmt[i]);
				break;
		};
	}
}
