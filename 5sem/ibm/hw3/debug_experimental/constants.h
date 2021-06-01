#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <stdio.h>
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
#include <sched.h>
#include <sys/sysinfo.h>

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#define CANNOT_OPEN_FILE -1
#define CANNOT_READ_FILE -2
#define INVALID_FILE -3

#define INCONSISTENT_SYSTEM -4
#define INCONSISTENT_BLOCK -5
#define EPS 1e-17

#define OK 0

#endif //CONSTANTS_H
