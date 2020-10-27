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

//Быстрая сортировка
void quickSort(Student* a, int arrayLen)
{
    int l;
    Student x;
    if(arrayLen < 2) return ;
    while(arrayLen > 2)
    {
        x = a[arrayLen / 2];
        l = sksort(a, arrayLen, x);
        if(l < arrayLen - l)
        {
            quickSort(a, l);
            a += l;
            arrayLen -= l;
        }
        else
        {
            quickSort(a + l, arrayLen - l);
            arrayLen = l;
        }
    }
    if((arrayLen == 2) && (a[arrayLen - 2] > a[arrayLen - 1]))
    {
        a[arrayLen - 2].swap(a[arrayLen - 1]);
    }
    return ;
}

int sksort(Student* a, int arrayLen, Student x)
{
    int left = 0;
    int right = arrayLen - 1;
    while(left <= right)
    {
        while(a[left] < x)
        {
            left ++;
        }
        while(a[right] > x)
        {
           right --;
        }
        if(left <= right)
        {
            a[left].swap(a[right]);
            right --;
            left ++;
        }
    }
    return left;
}

