#include "sort.h"
#include "student.h"

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

//Сортировка пузырьком
void bubbleSort(Student* a, int arrayLen)
{
    bool fl;
    for(int i = arrayLen - 1; i >= 0; i --)
    {
        fl = true;
        for(int j = 0;j < i;j ++)
        {
            if(a[j] > a[j+1])
            {
                a[j].swap(a[j + 1]);
                fl = false;
            }
        }
        if(fl)
        {
            break;
        }
    }
}
