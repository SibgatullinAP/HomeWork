void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
  
void sort_array(int size, int arr[])
{
   for (int i = 0; i < size - 1; i++)       
       for (int j = 0; j < size - i - 1; j++) 
           if (arr[j] > arr[j + 1])
              swap(&arr[j], &arr[j + 1]);
}