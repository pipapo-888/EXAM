#include <stdlib.h>
#include <stdio.h>

int count_digit(int nbr)
{
	int digit = 0;
	if (nbr <= 0)
	{
		digit++;
		nbr = -nbr;
	}
	while (nbr)
	{
		nbr /= 10;
		digit++;
	}
	return (digit);
}

char	*ft_itoa(int nbr)
{
	int		digit = count_digit(nbr);
	char	*number = malloc(digit + 1);
	if (!number)
		return (NULL);
	number[digit] = '\0';
	if (nbr < 0)
	{
		number[0] = '-';
		nbr = -nbr;
	}
	if (nbr == 0)
		number[0] = '0';
	while (nbr)
	{
		number[--digit] = nbr % 10 + '0';
		nbr /= 10;
	}
	return (number);
}

int main()
{
	int num = -123;
	char *number = ft_itoa(num);

	printf("%s", number);

}
