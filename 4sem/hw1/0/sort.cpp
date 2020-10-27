#include "sort.h"
#include "student.h"
#include "myexeption.h"

#include <time.h>


bool isSorting(int sortType, int arrayLen, Student* a, Student* b)
{
    if(sortType > 7 || sortType < 1)
    {
        printf("Choosen type isn't in list, please select other type of sorting\n");
        return false;
    }   
    double timer = 0;
    switch(sortType)
    {
        case BUBBLE_SORT:
            timer = clock();
            bubbleSort(a, arrayLen);
            timer = clock() - timer;
            break;
        case LINEAR_INSERTION_SORT:
            timer = clock();
            linInsSort(a, arrayLen);
            timer = clock() - timer;
            break;
        case FINDING_MINIMUM_SORT:
            timer = clock();
            minSort(a, arrayLen);
            timer = clock() - timer;
            break;
        case BINARY_SEARCH_SORT:
            timer = clock();
            binInsSort(a, arrayLen);
            timer = clock() - timer;
            break;
        case MERGE_SORT:
            b = new Student [arrayLen];
            if(!b){
                printf("Sorry, not enough memmory for alloctaion\n");
                return false;
            }
            timer = clock();
            mergeSort(a, arrayLen, b);
            timer = clock() - timer;
            delete [] b;
            break;
        case QUICK_SORT:
            timer = clock();
            quickSort(a, arrayLen);
            timer = clock() - timer;
            break;
        case HEAP_SORT:
            timer = clock();
            heapSort(a, arrayLen);
            timer = clock() - timer;
            break; 
        default:
            printf("Choosen type isn't in list, please select other type of sorting\n");
            return false;
    }
    printf("Time = %lf\n", timer / CLOCKS_PER_SEC);
    bool ret = checkSort(a, arrayLen); 
    return ret;
}

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

//Линейная вставка
void linInsSort(Student* a, int arrayLen)
{
    for(int i = 1; i < arrayLen; i ++)
    {
        for(int j = i; (j > 0) && (a[j - 1] > a[j]); j --)
        {
            a[j-1].swap(a[j]);
        }
    }
}

//Сортировка поиском минимума
void minSort(Student* a, int arrayLen)
{
    int k;
    Student min;
    for(int i = 0; i < (arrayLen - 1); i ++)
    {
        min = a[i];
        for(int j = i; j <= (arrayLen - 1); j++)
        {
            if(!(a[j] > min))
            {
                k = j;
                min = a[j];
            }
        }
        a[i].swap(a[k]);
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
    int j, k;
    for(int i = 1; i < arrayLen; i++)
    {
        j = binsearch(a, i, a[i]);
        for(k = i; k > j; k --)
        {
            a[k-1].swap(a[k]);
        }
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
            c[k] = a[i];
            i ++;
            k ++;
        }
        else
        {
            c[k] = b[j];
            j ++;
            k ++;
        }
    }
    while(i <arrayLen)
    {
        c[k] = a[i];
        i ++;
        k ++;
    }
    while(j < m)
    {
        c[k] = b[j];
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
            b[k] = a[k];
        }
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

//Турнирная сортировка

void heapSort(Student* a, int arrayLen)
{
    int i;
    for (i = ( arrayLen / 2) - 1; i >= 0; i --)
    {
        createheap(a, i, arrayLen - 1);
    }
    for (i = arrayLen - 1; i >= 1; i --)
    {
        a[0].swap(a[i]);
        createheap(a, 0, i - 1);
    }
}

void createheap(Student* a, int root, int bottom)
{
    int fl = 0, max;
    while ((root * 2 <= bottom) && (!fl))
    {
        if (root * 2 == bottom)
        {
            max = root * 2;
        }
        else
        {
            if (a[root * 2] > a[root * 2 + 1])
            {
                max = root * 2;
            }
            else
            {
                max = root * 2 + 1;
            }
            if(a[root] < a[max])
            {
                a[root].swap(a[max]);
                root = max;
            }
            else
            {
                fl = 1;
            }
        }
    }
}


