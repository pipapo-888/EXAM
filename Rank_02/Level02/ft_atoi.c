#include <stdio.h>

int ft_atoi(char *str)
{
	int result = 0;
	int minus = 1;
	int i = 0;

	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			minus = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return(result * minus);
}

int main()
{
	char number[] = "   -8888890";

	int num = ft_atoi(number);
	printf("%d", num);

	return (0);
}
