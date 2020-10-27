#include <stdio.h>
#include <iostream>
#include <time.h>

#include"const.h"
#include "student.h"
#include "biDirAddons.h"
#include "biDirList.h"
#include "biDirListNode.h"

int main(int argc, char const *argv[])
{
    //signal(SIGSEGV, posix_death_signal);

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

    List a;
    ret = read_list(argv[1], a);
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

    printf("\n--------------------------------------------------------------");
    printf("\nPlease choose the type of sorting, by entering number of sort.\n");
    printf("BubbleSort - 1\nMaxFindingSort - 2\nMinFindingSort - 3\n");
    printf("LinInsertionSort - 4\nNewman's Sort - 5\nQuickSort - 6\n");
    printf("Type = ");
    int sortSelector = 0;
    if (!scanf("%d", &sortSelector) || (sortSelector > 7 || sortSelector < 1))
    {
        printf("Incorrect input values. Please enter number from 1 to 7\n");
        a.delete_list();
        return -4;
    }
    printf("---------\n\n");

    bool (*comp)(ListNode*, ListNode*);
    int compSelector = 0;
    printf("------------------------------\n");
    printf("Please choose comparator type.\nFor UPside sorting enter 1\nFor DOWNside sorting enter 2\n");
    printf("Your chose = ");
    if (!scanf("%d", &compSelector) || (compSelector != 1 && compSelector != 2))
    {
        printf("Incorrect input values. Please enter 1 or 2\n");
        a.delete_list();
        return -5;
    }
    printf("------------------------------\n\n");
    switch(compSelector)
    {
        case 1:
            comp = compareMore;
            break;
        case 2:
            comp = compareLess;
            break;
        default:
            comp = compareMore;
            break;
    }

    printf("-------\n");
    printf("BEFORE:\n");
    printf("-------\n");
    a.print();

    double time = clock();
    if (checkSort(&a, comp))
    {
        time = (clock() - time) / CLOCKS_PER_SEC;
        printf("-------\n");
        printf("AFTER:\n");
        printf("-------\n");
        a.print();
        printf("Time = %lf\n", time);
        a.delete_list();
        return 0;
    }

    switch(sortSelector)
    {
        case BUBBLE_SORT:
            time = clock();
            a.bubbleSort(comp);
            time = (clock() - time) / CLOCKS_PER_SEC;
            break;
        case MAX_FIN_SORT:
            time = clock();
            a.maxFinSort(comp);
            time = (clock() - time) / CLOCKS_PER_SEC;
            break;
        case MIN_FIN_SORT:
            time = clock();
            a.minFinSort(comp);
            time = (clock() - time) / CLOCKS_PER_SEC;
            break;
        case LIN_IN_SORT:
            time = clock();
            a.linInsSort(comp);
            time = (clock() - time) / CLOCKS_PER_SEC;
            break; 
        case NEWMAN_SORT:
            time = clock();
            a.mergeSort(comp);
            time = (clock() - time) / CLOCKS_PER_SEC;
            break;
        case QUICK_SORT:
            time = clock();
            a.callQuickSort(comp);
            time = (clock() - time) / CLOCKS_PER_SEC;
            break;
        default:
            printf("Sorting type wasn't chosen\n");
            a.delete_list();
            return 0;
            break;
    }

    printf("-------\n");
    printf("AFTER:\n");
    printf("-------\n");
    a.print();
    checkSort(&a, comp);

    printf("Time = %lf\n", time);

    a.delete_list();
    return 0;
}
