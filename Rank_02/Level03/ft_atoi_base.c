#include <stdio.h>

int ft_atoi_base(const char *str, int str_base)
{
	int minus = 1;
	int result = 0;
	if (*str == '-')
	{
		minus *= -1;
		str++;
	}
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			result = result * str_base + (*str - '0');
		else if (*str >= 'A' && *str <= 'F')
			result = result * str_base + (*str - '7');
		else if (*str >= 'a' && *str <= 'f')
			result = result * str_base + (*str - 'W');
		str++;
	}
		return(result * minus);
}

int main()
{
	int base = 16;

	char num[] = "10";

	int numnum = ft_atoi_base(num, base);

	printf("%d", numnum);

	return (0);
}
