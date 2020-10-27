#ifndef ADDONS_H
#define ADDONS_H

#include "student.h"
#include "tree.h"
#include "treeNode.h"

#define LOGOWIDTH 1000
#define MAX_PRINT 5
#define NOT_ERROR_END_OF_INPUT 1
#define ERROR_CANNOT_OPEN_INPUT_FILE -1
#define ERROR_CANNOT_INITIALIZE_STUDENT_NAME -2
#define ERROR_CANNOT_READ_INPUT_FILE -3
#define ERROR_CANNOT_ALLOCATE_MEMMORY -4

int read_tree(const char* name, Tree & a);
int logo1(bool selector = false, const char* inputfile = "art.txt");
int logo2(bool selector = false, const char* inputfile = "sad.txt");
void posix_death_signal(int signum);


#endif // ADDONS_H
