#include <stdio.h>
#include <string.h>

ssize_t	ft_strlen(char *str)
{
	ssize_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

void	sort_str(char *str)
{
	ssize_t	len;
	char	c;

	len = ft_strlen(str);
	for (int i = 0; i < len; i++)
	{
		for (int j = i + 1; j < len; j++)
		{
			if (str[i] > str[j])
			{
				c = str[i];
				str[i] = str[j];
				str[j] = c;
			}
		}
	}
}

void	swap(char *a, char *b)
{
	char	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	reverse(char *s, int start, int end)
{
	while (start < end)
	{
		swap(&s[start], &s[end]);
		start++;
		end--;
	}
}

int	next_permutation(char *s, int len)
{
	int	i;
	int	j;

	i = len - 2;
	while (i >= 0 && s[i] >= s[i + 1])
		i--;
	if (i < 0)
		return (0);
	j = len - 1;
	while (s[j] <= s[i])
		j--;
	swap(&s[i], &s[j]);
	reverse(s, i + 1, len - 1);
	return (1);
}

int	main(int ac, char **av)
{
	if (ac != 2 || av[1][0] == '\0')
	{
		printf("WRONG\n");
		return (1);
	}
	sort_str(av[1]);
	int len = ft_strlen(av[1]);

	// dfs(av[1], 0);
	do {
		puts(av[1]);
	} while (next_permutation(av[1], len));

	return (1);
}