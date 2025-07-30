#include <stdio.h>
#include <stdlib.h>


// int ft_isprime(int nbr)
// {
// 	printf("%d", nbr);
// 	if (nbr < 2)
// 		return (0);
// 	if (nbr == 2)
// 		return(1);
// 	int i = 3;
// 	while (i < nbr)
// 	{
// 		if (nbr % i == 0)
// 			return (0);
// 		i += 2;
// 	}
// 	return (1);
// }

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("\n");
		return (0);
	}
	int nbr = atoi(argv[1]);
	int i = 2;

	if (nbr == 1)
		printf("1");

	while (nbr != 1)
	{
		if (nbr % i == 0)
		{
			printf("%d", i);
			nbr /= i;
			if (nbr != 1)
				printf("*");
			i = 2;
		}
		i++;
	}
	printf("\n");
	return (0);
}
