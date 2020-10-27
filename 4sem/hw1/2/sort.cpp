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

//Линейная вставка
void linInsSort(Student* a, int arrayLen)
{
    int  j = 0, m;
    Student tmp;
    for (int i = 1; i < arrayLen; i++)
    {
        for (j = 0; a[i] > a[j];j ++);
        //tmp = a[i];
        tmp.copy(a[i]);
        for (m = i; m > j; m--)
        {
            //a[m]=a[m-1];
            a[m].copy(a[m - 1]);
        }
        //a[j]=tmp;
        a[j].copy(tmp);

    }
    tmp.init(0, 0);
}
