#ifndef SORT_H
#define SORT_H 

#include "student.h"
bool checkSort(Student* a, int arrayLen);

void mergeSort(Student* a, int arrayLen, Student *b);
void insert(Student* a, int arrayLen, Student *b, int m, Student *c);

#endif
