#include <stdio.h>
#include <string.h>

// int is_valid(char *str)
// {
// 	int opened = 0, closed = 0;

// 	for (int i = 0; str[i]; i++)
// 	{
// 		if (str[i] == '(')
// 			opened++;
// 		else if (str[i] == ')')
// 		{
// 			if (opened > 0)
// 				opened--;
// 			else
// 				closed++;
// 		}
// 	}
// 	return (opened + closed);
// }

// void dfs(char *str, int must_fix, int n_fixed, int pos)
// {
// 	if (must_fix == n_fixed && is_valid(str) == 0)
// 	{
// 		puts(str);
// 		return ;
// 	}
// 	for (int i = pos; str[i]; i++)
// 	{
// 		if (str[i] == '(' || str[i] == ')')
// 		{
// 			int c = str[i];
// 			str[i] = ' ';
// 			dfs(str, must_fix, n_fixed + 1, i);
// 			str[i] = c;
// 		}
// 	}
// }

// int	main(int ac, char **argv)
// {

// 	if (ac != 2)
// 	{
// 		puts("WRONG AC");
// 		return (1);
// 	}
// 	int m_fix = is_valid(argv[1]);
// 	dfs(argv[1], m_fix, 0, 0);

// 	return (0);
// }

// int is_valid(char *str)
// {
// 	int opened = 0, closed = 0;

// 	for (int i = 0; str[i]; i++)
// 	{
// 		if (str[i] == '(')
// 			opened++;
// 		else if (str[i] == ')')
// 		{
// 			if (opened > 0)
// 				opened--;
// 			else
// 				closed++;
// 		}
// 	}
// 	return (opened + closed);
// }

// void dfs(char *str, int must_fix, int n_fixed, int pos)
// {
// 	if (must_fix == n_fixed && is_valid(str) == 0)
// 	{
// 		puts(str);
// 		return ;
// 	}
// 	for (int i = pos; str[i]; i++)
// 	{
// 		if (str[i] == '(' || str[i] == ')')
// 		{
// 			char c = str[i];
// 			str[i] = '_';
// 			dfs(str, must_fix, n_fixed + 1, i);
// 			str[i] = c;
// 		}
// 	}
// }

// int main(int ac, char **av)
// {
// 	if (ac != 2 || av[1][0] == '\0')
// 		return(printf("WRONG"), 1);
// 	int m_fix = is_valid(av[1]);

// 	dfs(av[1], m_fix, 0, 0);

// }

int	is_valid(char *str)
{
	int opened, closed;
	opened = 0, closed = 0;
	for (int i = 0; str[i]; i++)
	{
		if (str[i] == '(')
			opened++;
		else if (str[i] == ')')
		{
			if (opened > 0)
				opened--;
			else
				closed++;
		}
	}
	return (opened + closed);
}

void	dfs(char *str, int must_fix, int n_fixed, int pos)
{
	char	c;

	if (must_fix == n_fixed && !is_valid(str))
	{
		puts(str);
		return ;
	}
	for (int i = pos; str[i]; i++)
	{
		if (str[i] == '(' || str[i] == ')')
		{
			c = str[i];
			str[i] = '_';
			dfs(str, must_fix, n_fixed + 1, i + 1);
			str[i] = c;
		}
	}
}

int	main(int ac, char **av)
{
	if (ac != 2 || av[0][1] == '\0')
	{
		printf("WRONG");
		return (1);
	}
	int must_fix = is_valid(av[1]);
	dfs(av[1], must_fix, 0, 0);

	return (0);
}