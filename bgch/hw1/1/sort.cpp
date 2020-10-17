#include "sort.h"

int read (const char *file_name, double *arr, int size)
{
  FILE *file = fopen (file_name, "r");
  if (file == NULL)
    return CANNOT_OPEN_FILE;

  for (int i = 0; i < size; i ++)
    {
      if (fscanf (file, "%lf", (arr + i)) != 1)
        {
          fclose (file);
          return CANNOT_READ_FILE;
        }
    }

  fclose (file);
  return 0;
}

void print (double *arr, int size)
{
  int print_limit = ((size > MAX_PRINT) ? MAX_PRINT : size);
  for (int i = 0; i < print_limit; i++)
    printf ("\t[%d] = %.4f\n", i, arr[i]);
}

void check (double *arr, int size)
{
  for (int i = 0; i < size - 1; i++)
    {
      if (arr[i] > arr[i+1])
        {
          printf ("\x1b[31m[UNSORTED]\x1b[0m\n");
          return;
        }
    }
  printf ("\x1b[32m[SORTED]\x1b[0m\n");
}

void swap (double *a, int i, int j)
{
  double buff = a[j];
  a[j] = a[i];
  a[i] = buff;
}


//3_1
int binary_search (const double *arr, int size, double x)
{
  int left = 0;
  int right = size - 1;
  int center;

  if (arr[left] > x)
    return 0;
  if (arr[right] < x)
    return size;

  while (left <= right)
    {
      center = (left + right) / 2;
      if (arr[center] <= x)
        left = center + 1;
      else
        right = center - 1;
    }

  return left;
}

//3_2
void merge(const double *arr_1, int size_1,
           const double *arr_2, int size_2, double *result)
{
  int i = 0, j = 0, k = 0;
  while ((i < size_1) && (j < size_2))
    {
      if (arr_1[i] < arr_2[j])
        {
          result[k] = arr_1[i];
          i++;
          k++;
        }
      else
        {
          result[k] = arr_2[j];
          j++;
          k++;
        }
    }

  while (i < size_1)
    {
      result[k] = arr_1[i];
      i++;
      k++;
    }

  while (j < size_2)
    {
      result[k] = arr_2[j];
      j++;
      k++;
    }
}

//3_3
int array_redbuilding (double *arr, int size, double x)
{
  int left = 0;
  int right = size - 1;
  while (left <= right)
    {
      while (left < size && arr[left] < x)
        left++;
      while (right >= 0 && arr[right] > x)
        right--;
      if (left <= right)
        {
          swap (arr, left, right);
          right--;
          left++;
        }
    }

  return left;
}

//3_4
void binary_sort (double *arr, int size)
{
  for(int i = 1; i < size; i++)
    {
      int j = binary_search (arr, i, arr[i]);
      for (int k = i; k > j; k--)
        swap (arr, k, k - 1);
    }
}

//3_5
void merge_sort (double *arr_1, double *arr_2, int size)
{
  double *pr_temp = NULL;
  double *arr_1_temp = arr_1;
  int tail_len = 0, i = 0;
  for (int seg_len = 1; seg_len < size; seg_len <<= 1)
    {
      for (i = 0; (i + 2 * seg_len) <= size; i += (seg_len * 2))
        merge (arr_1 + i, seg_len, arr_1 + seg_len + i, seg_len, arr_2 + i);

      merge (arr_1 + i, size - i - tail_len,
             arr_1 + size - tail_len, tail_len, arr_2+i);
      tail_len = size - i;

      pr_temp = arr_1;
      arr_1 = arr_2;
      arr_2 = pr_temp;
    }
  if (arr_1_temp != arr_1)
    {
      for (int k = 0; k < size; k++)
        arr_2[k] = arr_1[k];
    }
}

//3_6
void quick_sort (double *arr, int size)
{
  int position;
  double base_element;

  if (size < 2)
    return ;

  while (size > 2)
    {
      base_element = arr[size / 2];
      position = array_redbuilding (arr, size, base_element);
      if (position < size - position)
        {
          quick_sort (arr, position);
          arr += position;
          size -= position;
        }
      else
        {
          quick_sort (arr + position, size - position);
          size = position;
        }
    }
  if (size == 2 && arr[size - 2] > arr[size - 1])
    swap (arr, size - 2, size - 1);

  return ;
}

//3_7
void heap_sort (double *arr, int size)
{
  create_heap(arr, size);

  for (int i = size - 1; i > 0; i--)
    {
      rebuild_heap(arr, i);
    }
}


void create_heap (double *arr, int size)
{
  for (int i = 1; i < size; i++)
    {
      int i_temp = i;
      for (int j = (i - 1) >> 1; i_temp > 0; j = (j - 1) >> 1)
        {
          if (!(arr[j] < arr[i]))
            break;
          i_temp = j;
        }

      double buff = arr[i];
      for (int j = i; j > i_temp; j = (j - 1) >> 1)
        arr[j] = arr[(j - 1) >> 1];

      arr[i_temp] = buff;
    }
}

void rebuild_heap (double  *arr, int depth)
{
  double buff = arr[depth];
  swap(arr, 0, depth);

  int i = 0;
  for (int j = (i << 1) + 1; j < depth; j = (i << 1) + 1)
    {
      if ((j < depth - 1) && (arr[j] < arr[j + 1]))
        j++;

      if(buff < arr[j])
        {
          arr[i] = arr[j];
          i = j;
        }
      else
        break;
    }
  arr[i] = buff;
}