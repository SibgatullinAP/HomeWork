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

//Сортировка бинарной вставкой
int binsearch(Student* a, int arrayLen, Student x)
{
    int s;
    int left = 0;
    int right = arrayLen - 1;
    if(a[left] > x)
    {
        return 0;
    }
    if(a[right] < x)
    {
        return arrayLen;
    }
    while(left <= right)
    {
        s = (left + right) / 2;
        if(!(a[s] > x))
        {
            left = s + 1;
        }
        else
        {
            right = s - 1;
        }
    }
    return left;
}

void binInsSort(Student* a, int arrayLen)
{
    Student tmp;
    int j;
    for(int i = 1; i < arrayLen; i++)
    {
        j = binsearch(a, i, a[i]);
        //tmp = a[i];
        tmp.copy(a[i]);

        for (int k = i; k > j; k --)
        {
            //a[k] = a[k - 1];
            a[k].copy(a[k-1]);
        }
        //a[j] = tmp;
        a[j].copy(tmp);

    }
    tmp.init(0, 0);
}
