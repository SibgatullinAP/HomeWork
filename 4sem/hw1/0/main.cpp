#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>

#include "student.h"
#include "sort.h"
#include "addons.h"

int main(int argc, char const *argv[])
{
    int arrayLen = 0;
    if(((argc != 3) || !(arrayLen = atoi(argv[1]))))
    {
        printf("Usage: %s list_len file_name\n", argv[0]);
        return 1;
    }

    Student* a = new Student[arrayLen];
    if(a == nullptr)
    {
        printf("Sorry, not enough memmory for alloctaion\n");
        return -2;
    }

    if(int ret = read_array(argv[2], a, arrayLen) < 0)
    {
        printf("ERROR: %d\n",ret );
        return -4;
    }

    printf("-------\n");
    printf("Before:\n");
    printf("-------\n");
    print_array(a, arrayLen);

    printf("Please choose the type of sorting:\n1.Bubble sort\n2.Linear insertion sort\n3.Sorting with findig minimum\n4.Sorting with binary search\n");
    printf("5.Merge sort (Newman's sort)\n6.Quicksort\n7.Heap sort\nYour choice = ");
    int sortType = 0;
    if(scanf("%d", &sortType)!=1)
    {
        printf("Incorrect input values\n");
        return -3;
    }

    printf("-------\n");
    bool result = isSorting(sortType, arrayLen, a, nullptr);
    if(result) printf("FINE!\n");
    else return printf("Something going wrong :(\n"), -5;
    printf("-------\n");

    printf("------\n");
    printf("After:\n");
    printf("------\n");
    print_array(a, arrayLen);

    delete [] a;
    return 0;
}
