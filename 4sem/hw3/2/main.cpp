#include <stdio.h>
#include <iostream>
#include <time.h>

#include "student.h"
#include "func.h"
#include "addons.h"
#include "list.h"
#include "listNode.h"

int main(int argc, char const *argv[])
{
    int shift = 0;
    if(argc != 3 || ! (shift = atoi(argv[2])))
    {
        printf("Usage: %s file_name\n", argv[0]);
        return -1;
    }

    List a;

    int ret = read_list(argv[1], a);
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
            case ERROR_CANNOT_ALLOCATE_MEMMORY:
                printf("ERROR_CANNOT_ALLOCATE_MEMMORY\n");
                break;
            default:
                printf("UNKNOWN_ERROR = %d\n", ret);
                break;
        }
        a.delete_list();
        return -3;
    }

    printf("-------\n");
    printf("BEFORE:\n");
    printf("-------\n");
    a.print();

    double time = clock();
    a.func(shift); // передавать ссылкой или нет ??
    time = (clock() - time) / CLOCKS_PER_SEC;

    printf("-------\n");
    printf("AFTER:\n");
    printf("-------\n");
    a.print();

    printf("Time = %lf\n", time);

    a.delete_list();
    return 0;
}
