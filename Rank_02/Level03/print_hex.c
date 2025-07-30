#include <unistd.h>
#include <stdio.h>

int ft_atoi(char *num)
{
	int	number = 0;
	int	i = 0;

	while (num[i] >= '0' && num[i] <= '9')
	{
		number = number * 10 + (num[i] - '0');
		i++;
	}
	return (number);
}
void put_hex(int num)
{
	char hex[] = "0123456789abcdef";
	char c;

	if (num >= 16)
		put_hex(num / 16);
	c = hex[num % 16];
	write(1, &c, 1);
	return ;
}

void	print_hex(char *number)
{
	int	num = ft_atoi(number);
	put_hex(num);
	return ;
}

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		write(1, "\n", 1);
		return (0);
	}
	print_hex(argv[1]);


	return (0);
}
