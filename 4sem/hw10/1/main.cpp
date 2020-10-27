#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <stdlib.h>

#include "student.h"
#include "treeNode.h"
#include "tree.h"
#include "addons.h"
#include "const.h"

int main(int argc, char const *argv[])
{

    if(argc != 3)
    {
        printf("Usage: %s file_name btree_basis_value\n", argv[0]);
        return -1;
    }

    int btree_basis = atoi(argv[2]);
    if(btree_basis < 1)
    {
        printf("Incorrect btree_basis_value !\n");
        return -1;
    }

    Tree a (btree_basis);
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
        a.deleteTree(a.getRoot());
        return -2;
    }

    printf("-------\n");
    printf("Tree of student:\n");
    printf("-------\n");
    a.print(a.getRoot());

    /*for(;;)
    {
        double time = clock();
        int answer = a.func1(a.get_root(), k);
        time = (clock() - time) / CLOCKS_PER_SEC;    
    }

    printf("Answer = %d\nTime = %lf\n", answer, time);
    */
    
    a.deleteTree(a.getRoot());
    return 0;
}
