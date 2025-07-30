#include <stdio.h>

int max(int* tab, unsigned int len)
{
	if (len == 0)
		return (0);
	int max;
	int temp;
	int i = 1;
	max = tab[0];

	while(--len)
	{
		if (tab[i] > max)
			max = tab[i];
		i++;
	}
	return max;
}

int main()
{
	int array[] = {123, 3, 4, 500, 12333};

	int max_num = max(array, 7);
	printf("%d", max_num);
	return (0);
}
