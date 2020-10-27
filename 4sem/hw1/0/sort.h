#ifndef SORT_H
#define SORT_H 

#include "student.h"

#define BUBBLE_SORT 1
#define LINEAR_INSERTION_SORT 2
#define FINDING_MINIMUM_SORT 3
#define BINARY_SEARCH_SORT 4
#define MERGE_SORT 5
#define QUICK_SORT 6
#define HEAP_SORT 7

bool isSorting(int sortType, int arrayLen, Student* a, Student* b = nullptr);
bool checkSort(Student* a, int arrayLen);

void bubbleSort(Student* a, int arrayLen);

void linInsSort(Student* a, int arrayLen);

void minSort(Student* a, int arrayLen);

int binsearch(Student* a, int arrayLen, Student x);
void binInsSort(Student* a, int arrayLen);

void insert(Student* a, int arrayLen, Student *b, int m, Student *c);
void mergeSort(Student* a, int arrayLen, Student *b);

void quickSort(Student* a, int arrayLen);
int sksort(Student* a, int arrayLen, Student x);

void createheap(Student* a, int root, int bottom);
void heapSort(Student* a, int arrayLen);

#endif
