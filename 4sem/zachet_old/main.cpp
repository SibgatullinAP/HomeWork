#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <stdlib.h>

#include "addons.h"
#include "list.h"
#include "listNode.h"
#include "string.h"
#include <string.h>
int main(int argc, char const *argv[])
{
    if(argc != 3)
    {
        printf("Usage: %s file_name string_s\n", argv[0]);
        return -1;
    }
    const char *s = argv[2];

    List a;
    int ret = read(argv[1], a);
    if(ret < 0)
    {
        switch(ret)
        {
            case ERROR_CANNOT_OPEN_INPUT_FILE:
                printf("ERROR_CANNOT_OPEN_INPUT_FILE\n");
                break;
            case ERROR_CANNOT_INITIALIZE_STRING_NAME:
                printf("ERROR_CANNOT_INITIALIZE_STRING_NAME\n");
                break;
            case ERROR_CANNOT_READ_INPUT_FILE:
                printf("ERROR_CANNOT_READ_INPUT_FILE\n");
                break;
            case ERROR_CANNOT_ALLOCATE_MEMMORY:
                printf("ERROR_CANNOT_ALLOCATE_MEMMORY\n");
                break;
            case ERROR_EMPTY_INPUT_FILE:
                printf("ERROR_EMPTY_INPUT_FILE\n");
                break;
            default:
                printf("UNKNOWN_ERROR = %d\n", ret);
                break;
        }
        a.delete_list();
        return -2;
    }

    printf("\nLIST BEFORE FUNCTION:\n");
    a.print();

    double t = clock();
    a.func(s);
    t = clock() - t;

    printf("\nLIST AFTER FUNCTION:\n");
    a.print();
    printf("\nTime = %lf\n", t/CLOCKS_PER_SEC);

    a.delete_list();
    return 0;
}
