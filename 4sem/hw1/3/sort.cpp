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

//Сортировка поиском минимума
void minSort(Student* a, int arrayLen)
{
    int k;
    Student min;
    for(int i = 0; i < (arrayLen - 1); i ++)
    {
        //min = a[i];
        min.copy(a[i]);
        for(int j = i; j <= (arrayLen - 1); j++)
        {
            if(!(a[j] > min))
            {
                k = j;
                //min = a[j];
                min.copy(a[j]);
            }
        }
        a[i].swap(a[k]);
    }
    min.init(0, 0);
}
