#include "addons.h"

int Printf(int fd, const char * format, ...)
{
    va_list ap;
    va_start(ap,format);

    char buff[LEN_STR];
    int ret = vsnprintf(buff, BUFF_LEN, format, ap);

    int len = ret + 1;
    if((ssize_t)sizeof(int) != write(fd, &len, sizeof(int)))
    {
	va_end(ap);
	return ERROR_SERVER_CANNOT_PRINT;
    }

    int nbytes = 0;
    for (int i = 0; len > 0; i += nbytes, len -= nbytes)
    {
	nbytes = write(fd, buff + i, len);
	if(nbytes <= 0)
	{
	    va_end(ap);
	    return ERROR_SERVER_CANNOT_PRINT;
	}
    }

    va_end(ap);
    return ret;
}

int Readf(int fd, char *buff)
{
    int len;
    if(read(fd, &len, sizeof(int)) != (int)sizeof(int))
    {
	return ERROR_SERVER_CANNOT_READ_INCORRECT_SIZE;
    }

    int nbytes = 0, i;
    for(i = 0; len > 0; i += nbytes, len -= nbytes)
    {
	nbytes = read(fd, buff + i, len);
	if(nbytes < 0)
	{
	    return ERROR_SERVER_CANNOT_READ;
	}
	if(nbytes == 0)
	{
	    return ERROR_SERVER_CLIPPED;
	}
    }

    return (i == 0 ? NOT_ERROR_SERVER_EMPTY_REQUEST : i);
}
