#include <stdio.h>
#include <time.h>

#include "student.h"
#include "treeNode.h"
#include "tree.h"
#include "addons.h"

int main(int argc, char const *argv[])
{
    if(argc != 2)
    {
        printf("Usage: %s file_name\n", argv[0]);
        return -1;
    }

    Tree a;
    
    int ret = read_tree(argv[1], a);
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

   /* double time = clock();
    int answer = func(a.get_head());
    time = (clock() - time) / CLOCKS_PER_SEC;

    printf("Answer = %d\nTime = %lf\n", answer, time);*/

    a.delete_tree(a.get_root());
    return 0;
}