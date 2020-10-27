#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory>
#include <stdarg.h>
#include <ctime>
#include <errno.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#define LEN 1024
#define BLEN 4096

int WritetoServer(int fd, const char *format, ...);
int ReadfromServer(int fd, char *buf);

int main(int argc, char **argv)
{
   	const char *SERVER_NAME; int SERVER_PORT;

    if (argc !=3 || !(SERVER_PORT = atoi(argv[2])) ) return printf ("Usage: %s SERVER_NAME SERVER_PORT\n", argv[0]), 1;
    SERVER_NAME = argv[1];

	int err, sock,ret;
	struct sockaddr_in server_addr;
	struct hostent *hostinfo;

	hostinfo = gethostbyname(SERVER_NAME);
	if (!hostinfo) return printf("Unknown host %s\n", SERVER_NAME), 1;
		
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	server_addr.sin_addr = *(struct in_addr *)hostinfo->h_addr;

	sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock < 0) return printf("Client: socket was not created\n"), 2;

	err = connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
	if(err < 0) return printf("Client: connection failure\n"), 3;
	fprintf(stdout,"Connection is ready\n");
	char buf[LEN];
	int k = 0;
	int p = 0;
	while (fgets (buf, LEN, stdin))
   	{
		for (ret = 0; buf[ret]  ; ret++)
		{
			if (buf[ret] == ';')
			{
				buf[ret] = 0; k = 1; break;
			}
		}
		if (k == 0) 
			continue;
		if (strcmp(buf, "quit") == 0) return close(sock), 0;
		if (strcmp(buf, "stop") == 0) p = 1;
		if (WritetoServer(sock, buf) < 0) printf (" cannot print to socket\n");
		if(p==1) return close(sock), 0;
		while (1)
		{
			err = ReadfromServer(sock, buf);
			if (err < 0)
			{
				printf("something bad\n");
				break;
			}
			else
			{
				if(strcmp(buf, "done") == 0 || strcmp(buf, "bad_command") == 0) break;
				printf("%s", buf);
			}
		}
		k = 0;
		p = 0;
    }

	return 0;
}


int WritetoServer(int fd, const char *format, ...)
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


int ReadfromServer(int fd, char *buf)
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
