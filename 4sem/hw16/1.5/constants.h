#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "enum.h"
#include "memory"
#include <cstring>
#include <time.h>
#include <stdio.h>
#include <iostream>

#define NOT_ERROR_CONTINUE 10000
#define END_OF_WORKING -1
#define EMPTY_REQUEST -2

#define ERROR_CANNOT_OPEN_INPUT_FILE -1
#define ERROR_CANNOT_OPEN_OUTPUT_FILE -2
#define ERROR_CANNOT_READ_INPUT_FILE -3
#define ERROR_CANNOT_WRITE_TO_OUTPUT_FILE -4
#define ERROR_WORKING_WITH_EMPTY_OBJECT -5
#define ERROR_CANNOT_ALLOCATE_MEMMORY_TO_READ_NAME -6
#define ERROR_INCORRECT_ENTERED_TYPE -7

#define BUFF_LEN 1024
#define SPACE_LEN 256
#define ESCAPE_LEN 3
#define MAX_PRINT_LIST 20
#define MAX_PRINT_TREE 5
#define MAX_PRINT_HASH 5

#endif // CONSTANTS_H
