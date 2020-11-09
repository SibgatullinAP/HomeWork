#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stddef.h>
#include <fenv.h>
#include <unistd.h>
#include <sched.h>
#include <sys/sysinfo.h>

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#define CANNOT_OPEN_FILE -1
#define CANNOT_READ_FILE -2
#define INVALID_FILE -3
#define INCONSISTENT_SYSTEM -10
#define INCONSISTENT_BLOCK -100
#define EPS 1e-16

#endif //CONSTANTS_H
