#include "sort.h"
#include "student.h"
#include "addons.h"

bool checkSort(Student* a, int arrayLen)
{
    int fl = 0;
    for (int i = 0; i < arrayLen - 1; ++ i)
    {
        if (a[i] > a[i + 1])
        {
            fl = 1;
            break;
        }
    }
    if (fl == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//Турнирная сортировка

void heapSort(Student* a, int arrayLen)
{
    createHeap(a,arrayLen);

    for (int k = arrayLen - 1; k > 0; --k)
    {
        a[0].swap(a[k]);
        createBranch(a,k);
    }
    if(a[0] > a[1]){
        a[1].swap(a[0]);
    }
}

void createHeap(Student* a, int arrayLen)
{
    int l;
    for (int i = 1; i <= arrayLen - 1 ; ++i)
    {
        l = i;
        for (int j = (i - 1) / 2 ; j > 0; j = (j - 1) / 2)
        {
            if(a[l] > a[j])
            {
                a[l].swap(a[j]);
                l = j;
            }
        }
        if(a[l] > a[0])
        {
            a[0].swap(a[l]);
        }
    }
}

void createBranch(Student* a, int arrayLen)
{
    int i = 0;
    while(i < (arrayLen - 1) / 2){
        if(!(a[i] > a[i * 2 + 1]) && !(a[i * 2 + 1] < a[i * 2 +2]) )
        {
            a[i].swap(a[i * 2 + 1]);
            i = i*2 + 1;
        }
        else{
            if(!(a[i] > a[i*2+2]) && !(a[i*2 +1] > a[i*2 +2])) 
            {
                a[i].swap(a[i * 2 + 2]);
                i = i * 2 +2;
            }
            else
            {
                i = arrayLen;
            }
        }
    }
}