#ifndef STRING__H
#define STRING__H

#include "constants.h"

int read (const char *file_name, char **arr, int size);
void print (char **arr, int size);
int array_rebuilding (char **arr, int size, int k, char *string);
void free_ (char **arr, int size);

#endif //STRING__H
