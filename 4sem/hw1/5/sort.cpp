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

//Сортировка слиянием
 void insert(Student* a, int arrayLen, Student *b, int m, Student *c)
{
    int i = 0, j = 0, k = 0;
    while((i <arrayLen) && (j < m))
    {
        if((a[i] < b[j]))
        {
            //c[k] = a[i];
            c[k].copy(a[i]);
            i ++;
            k ++;
        }
        else
        {
            //c[k] = b[j];
            c[k].copy(b[j]);
            j ++;
            k ++;
        }
    }
    while(i <arrayLen)
    {
        //c[k] = a[i];
        c[k].copy(a[i]);
        i ++;
        k ++;
    }
    while(j < m)
    {
        //c[k] = b[j];
        c[k].copy(b[j]);
        j ++;
        k ++;
    }
}

void mergeSort(Student* a, int arrayLen, Student *b)
{
    Student *c, *ao;
    int i = 0, ls, k, p = 0; // ls- lenght of sort
    ao = a;
    for(ls = 1; ls < arrayLen; ls *= 2)
    {
        for (i = 0; (i + 2 * ls) <= arrayLen; i += (ls * 2))
        {
            insert(a + i, ls, a + ls + i, ls, b + i);
        }
        insert(a + i, arrayLen - i - p, a + arrayLen - p, p, b + i);
        p = arrayLen - i;
        c = a;
        a = b;
        b = c;
    }
    if(ao != a)
    {
        for(k = 0; k < arrayLen; k ++)
        {
            //b[k] = a[k];
            b[k].copy(a[k]);
            a[k].init(0, 0);

        }
    }
    else
    {
        for (int i = 0; i < arrayLen; i++)
        {
            b[i].init(0, 0);
        }
    }
}
