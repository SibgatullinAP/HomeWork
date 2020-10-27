#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <stdlib.h>

#include "addons.h"
#include "list.h"
#include "listNode.h"
#include "tree.h"
#include "treeNode.h"
#include "queue.h"
#include "queueNode.h"
#include "student.h"

int main(int argc, char const *argv[])
{
    signal(SIGSEGV, posix_death_signal);
    if(argc != 5)
    {
        printf("Usage: %s file_name size_of_list size_of_tree size_of_queue\n", argv[0]);
        return -1;
    }

    int size_list = atoi(argv[2]);
    int size_tree = atoi(argv[3]);
    int size_queue = atoi(argv[4]);

    int ret = logo1(false);
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

    if(size_list < 1 || size_tree < 1 || size_queue < 1)
    {
        printf("Error: Size of each of structures should be more than 1\n");
        return -1;
    }

    List a;
    ret = read(argv[1], a, size_list, size_tree, size_queue);
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
            case ERROR_NOT_ENOUGH_ELEMENTS_IN_INPUT_FILE:
                printf("ERROR_NOT_ENOUGH_ELEMENTS_IN_INPUT_FILE\n");
                break;
            default:
                printf("UNKNOWN_ERROR = %d\n", ret);
                break;
        }
        a.delete_list();
        return -2;
    }

    a.menu();

    a.delete_list();
    return 0;
}
