#include <stdio.h>
#include <stdlib.h>

int	min(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

int denominator(int a, int b){
	int answer = min(a, b);

	while (1)
	{
		if (a % answer == 0 && b % answer == 0)
			return (answer);
		answer--;
	}
}

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		printf("\n");
		return (0);
	}
	int a = atoi(argv[1]);
	int	b = atoi(argv[2]);

	int answer = denominator(a, b);
	printf("%d\n", answer);

	return (0);
}
