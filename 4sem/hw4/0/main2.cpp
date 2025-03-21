#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <stdlib.h>

#include "student.h"
#include "treeNode.h"
#include "tree.h"
#include "addons.h"


void fall()
{
      int* p = 0x00000000; 
      *p = 13;
}

int main(int argc, char const *argv[])
{
    signal(SIGSEGV, posix_death_signal);

    if(argc != 2)
    {
        printf("Usage: %s file_name\n", argv[0]);
        return -1;
    }

   int ret = logo1(true);
    if(ret < 0)
    {
        switch(ret)
        {
            case ERROR_CANNOT_OPEN_INPUT_FILE:
                printf("ERROR_CANNOT_OPEN_INPUT_FILE\n");
                break;
            case ERROR_CANNOT_READ_INPUT_FILE:
                printf("ERROR_CANNOT_READ_INPUT_FILE\n");
                break;
            default:
                printf("UNKNOWN_ERROR = %d\n", ret);
                break;
        }
        return -2;
    }

    Tree a;
    ret = read_tree(argv[1], a);
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
        a.delete_tree(a.get_root());
        return -2;
    }

    printf("-------\n");
    printf("Tree of student:\n");
    printf("-------\n");
    a.print(a.get_root());

    double time = clock();
    int answer = a.func2(a.get_root());
    time = (clock() - time) / CLOCKS_PER_SEC;

    printf("Answer = %d\nTime = %lf\n", answer, time);

    a.delete_tree(a.get_root());
    return 0;
}