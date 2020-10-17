#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stddef.h>
#include <fenv.h>
#include <math.h>
#include <string.h>

#define MAX_PRINT 20
#define M_MAX_PRINT 10
#define N_MAX_PRINT 5
#define STRING_BUFF 1024

#define CANNOT_OPEN_FILE -1
#define CANNOT_READ_FILE -2
#define INVALID_FILE -3
#define EMPTY_FILE -4
#define NOT_ENOUGH_MEMMORY -5

#define CANNOT_OPEN_FILE_1 -10
#define CANNOT_OPEN_FILE_2 -100
#define CANNOT_READ_FILE_1 -20
#define CANNOT_READ_FILE_2 -200
#define INVALID_FILE_1 -30
#define INVALID_FILE_2 -300
#define EMPTY_FILE_1 -40
#define EMPTY_FILE_2 -400

#define SEQ_TYPE_UNKNOWN 0
#define SEQ_TYPE_ARITHMETICAL_PROGRESSION 1
#define SEQ_TYPE_GEOMETRICAL_PROGRESSION 2
#define SEQ_TYPE_CONST 3
#define SEQ_TYPE_NOT_ENOUGH_DATA 4


#endif //CONSTANTS_H
