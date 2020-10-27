#ifndef ADDONS_H
#define ADDONS_H

#include "student.h"
#include "list.h"
#include "listNode.h"

#define MAX_PRINT 10
#define NOT_ERROR_END_OF_INPUT 1
#define ERROR_CANNOT_OPEN_INPUT_FILE -1
#define ERROR_CANNOT_INITIALIZE_STUDENT_NAME -2
#define ERROR_CANNOT_READ_INPUT_FILE -3
#define ERROR_CANNOT_ALLOCATE_MEMMORY -4

int read_tree(const char* name, Tree & a);

#endif // ADDONS_H
