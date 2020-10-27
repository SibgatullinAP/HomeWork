#ifndef SORT_H
#define SORT_H 

#include "student.h"
bool checkSort(Student* a, int arrayLen);

void heapSort(Student* a, int arrayLen);
void createHeap(Student* a, int arrayLen);
void createBranch(Student* a, int arrayLen);

#endif
