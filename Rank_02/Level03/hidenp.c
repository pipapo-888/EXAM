#include <unistd.h>

void find_str(char *s1, char *s2)
{
	int i = 0;
	int j = 0;

	while (1)
	{
		if (s1[i] == s2[j])
			i++;
		j++;
		if (!s1[i])
		{
			write(1, "1", 1);
			return ;
		}
		if (!s2[j])
		{
			write(1, "0", 1);
			return ;
		}
	}
}


int main(int argc, char **argv)
{
	if (argc != 3)
	{
		write(1, "\n", 1);
		return (0);
	}
	find_str(argv[1], argv[2]);

	write(1, "\n", 1);
	return (0);
}
