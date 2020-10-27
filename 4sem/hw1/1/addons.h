#ifndef ADDONS_H
#define ADDONS_H

#include "student.h"

#define MAX_PRINT 10
#define ERROR_CANNOT_OPEN_INPUT_FILE -1
#define ERROR_CANNOT_INITIALIZE_STUDENT_NAME -2
#define ERROR_CANNOT_READ_INPUT_FILE -3

int read_array(const char* name, Student* a, int arrayLen);
void print_array(Student* a, int arrayLen);


#endif // ADDONS_H
