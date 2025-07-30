#include <stdlib.h>
#include <stdio.h>

int *ft_range(int start, int end)
{
	int len;
	int i = 0;
	if (start > end)
		len = start - end + 1;
	else
		len = end - start + 1;
	int *result = malloc(len * sizeof(int));
	if (!result)
		return (NULL);

	if (start < end)
	{
		while (len--)
			result[i++] = start++;
	}
	else
	{
		while(len--)
			result[i++] = start--;
	}
	return (result);
}

int main()
{
	int *array = ft_range(-1, 2);

    for (int i = 0; i < 11; i++)
    {
        printf("%d\n", array[i]);
    }

	return (0);
}
