#ifndef ADDONS_H
#define ADDONS_H

#include "constants.h"

#include <stdarg.h>
#include <errno.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

class DataBase;
class Command;

int Printf(int fd, const char * format, ...);
int Readf(int fd, char *buff);
int server(DataBase &Db, int PORT);

#endif // ADDONS_H
