
void swap_negmax_last(int size, int a[])
{
	int i = 0;
	int negmax = 0;
	int negmax_ind = 0;
	for (i = 0; i < size; ++i)
	{
		if (a[i] < 0)
		{
			negmax = a[i];
			negmax_ind = i;
			break;
		}
	}

	if (i == size)
		return;

	for (i = 0; i < size; ++i)
	{
		if (a[i] < 0 && a[i] > negmax)
		{
			negmax = a[i];
			negmax_ind = i;
		}
	}

	int tmp = a[size - 1];
	a[size - 1] = a[negmax_ind];
	a[negmax_ind] = tmp;
}