#ifndef COMMON_H
#define COMMON_H

#include <mpi.h>
#include <stdarg.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stddef.h>
#include <fenv.h>
#include <unistd.h>
#include <pthread.h>
#include <memory>
#include <functional>
#include <sched.h>
#include <sys/sysinfo.h>

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#define OK 0
#define CANNOT_OPEN_FILE -1
#define CANNOT_READ_FILE -2
#define INVALID_FILE -3

#define MAIN_PID 0
#define MAX_PRINT 20

#endif // COMMON_H
