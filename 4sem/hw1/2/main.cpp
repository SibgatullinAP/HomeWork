#include <stdio.h>
#include <iostream>
#include <time.h>

#include "student.h"
#include "sort.h"
#include "addons.h"

int main(int argc, char const *argv[])
{
    int arrayLen = 0;
    if(((argc != 3) || !(arrayLen = atoi(argv[1]))))
    {
        printf("Usage: %s list_len file_name\n", argv[0]);
        return -1;
    }

    Student* a = new Student[arrayLen];
    if(a == nullptr)
    {
        printf("Sorry, not enough memmory for alloctaion\n");
        return -2;
    }

    int ret = read_array(argv[2], a, arrayLen);
    if(ret < 0)
    {
        switch(ret)
        {
            case ERROR_CANNOT_OPEN_INPUT_FILE:
                printf("ERROR_CANNOT_OPEN_INPUT_FILE\n");
                break;
            case ERROR_CANNOT_INITIALIZE_STUDENT_NAME:
                printf("ERROR_CANNOT_INITIALIZE_STUDENT_NAME\n");
                break;
            case ERROR_CANNOT_READ_INPUT_FILE:
                printf("ERROR_CANNOT_READ_INPUT_FILE\n");
                break;
            default:
                printf("UNKNOWN_ERROR = %d\n", ret);
                break;
        }
        delete [] a;
        return -3;
    }

    printf("-------\n");
    printf("Before:\n");
    printf("-------\n");
    print_array(a, arrayLen);

    double time = clock();
    linInsSort(a,arrayLen);
    time = (clock() - time) / CLOCKS_PER_SEC;

    printf("------\n");
    printf("After:\n");
    printf("------\n");
    print_array(a, arrayLen);

    printf("-------\n");
    printf("Time = %lf\n", time);
    if(checkSort(a,arrayLen)) printf("FINE!\n");
    else printf("Something going wrong :(\n");
    printf("-------\n");

    delete [] a;
    return 0;
}
