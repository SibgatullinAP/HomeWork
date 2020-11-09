#ifndef TASK_H
#define TASK_H

#define CANNOT_OPEN_FILE -1
#define CANNOT_READ_FILE -2

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int task (const char * file_name);

#endif
