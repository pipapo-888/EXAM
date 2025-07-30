#include <unistd.h>
#include <string.h>

int ft_strchr(char *str, char c)
{
	int i = 0;

	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void write_inter(char *s1, char *s2)
{
	int table[256] = {0};
	int i = 0;

	while (s1[i])
	{
		if (table[s1[i]] == 0 && ft_strchr(s2, s1[i]))
		{
			table[s1[i]] = 1;
			write(1, &s1[i], 1);
		}
		i++;
	}
	return ;
}


int	main(int argc, char *argv[])
{
	if (argc != 3)
	{
		write(1, "\n", 1);
		return (0);
	}
	write_inter(argv[1], argv[2]);
	write(1, "\n", 1);
	return (0);
}
