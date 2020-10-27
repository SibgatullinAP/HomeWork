#include "Printf.h"

int PrinttoClient(int fd, const char *format, ...)
{
	char buf[BLEN];
	int ret, nbytes, i;;

	va_list ap;
	va_start(ap, format);
	ret = vsnprintf(buf, LEN, format, ap);

	int len = ret + 1;
	if (write(fd, &len, sizeof(int)) != (ssize_t)sizeof(int))
		return va_end(ap), -1;


	for (i = 0; len > 0; i += nbytes, len -= nbytes)
	{
		nbytes = write(fd, buf + i, len);
		if (nbytes <= 0)
			return va_end(ap), -1;
	}
	va_end(ap);
	return ret;
}


int ReadfromClient(int fd, char *buf)
{
	int nbytes, len, i;
	if (read(fd, &len, sizeof(int)) != (int)sizeof(int)) return -1;

	for (i = 0; len > 0; i += nbytes, len -= nbytes)
	{
		nbytes = read(fd, buf + i, len);
		if (nbytes < 0) 
			return -1;
		else 
			if (!nbytes) return -1;
	}

	if (!i) 
		return -1;
	else 
		return i;
}
