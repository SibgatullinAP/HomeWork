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
    if(argc != 2)
    {
        printf("Usage: %s file_name\n", argv[0]);
        return -1;
    }

    List a;
    
    /*
    FILE* fp;
    if(!(fp = fopen(argv[1], "r")))
        {
            return ERROR_CANNOT_OPEN_INPUT_FILE;    
        } 
    int ret = a.read(fp);
    fclose(fp);
    */

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
        return -2;
    }

    printf("-------\n");
    printf("List of student:\n");
    printf("-------\n");
    a.print();

    double time = clock();
    //int answer = func(a);
    time = (clock() - time) / CLOCKS_PER_SEC;

    //printf("Answer = %d\nTime = %lf", answer, time);

    a.delete_list();
    return 0;
}
