#include <stdio.h>
#include <stdlib.h>

static char *pos;

void error(char c)
{
	if (c == '\0')
		printf("Unexpected end of input\n");
	else 
		printf("Unexpected token '%c'\n", c);
	exit(1);
}

int parse_expr();

int parse_factor()
{
	int val;

	if (*pos == '(')
	{
		pos++;
		val = parse_expr();
		if (*pos != ')')
			error(*pos);
		pos++;
	}
	else if (*pos >= '0' && *pos <= '9')
	{
		val = *pos - '0';
		pos++;
	}
	else 
		error(*pos);
	return (val);
}

int parse_term()
{
	int val;

	val = parse_factor();
	while (*pos == '*')
	{
		pos++;
		val *= parse_factor();
	}

	return (val);
}

int parse_expr()
{
	int val;

	val = parse_term();
	while (*pos == '+')
	{
		pos++;
		val += parse_term();
	}
	return (val);	
}

int main(int ac, char *av[])
{
	if (ac != 2)
		return 1;
	pos = av[1];	

	int ans = parse_expr();
	if (*pos != '\0')
		error(*pos);
	printf("%d\n", ans);

	return (0);
}

// static char *pos;

// static void	error(char c)
// {
// 	if (c == '\0')
// 		printf("Unexpected end of input\n");
// 	else
// 		printf("Unexpected token '%c'\n", c);
// 	exit(1);
// }

// static int	parse_expr(void);

// static int	parse_factor(void)
// {
// 	int	val;

// 	if (*pos == '(')
// 	{
// 		pos++;
// 		val = parse_expr();
// 		if (*pos != ')')
// 			error(*pos);
// 		pos++;
// 	}
// 	else if (*pos >= '0' && *pos <= '9')
// 	{
// 		val = *pos - '0';
// 		pos++;
// 	}
// 	else
// 		error(*pos);
// 	return (val);
// }

// static int	parse_term(void)
// {
// 	int	val;

// 	val = parse_factor();
// 	while (*pos == '*')
// 	{
// 		pos++;
// 		val *= parse_factor();
// 	}
// 	return (val);
// }

// static int	parse_expr(void)
// {
// 	int	val;

// 	val = parse_term();
// 	while (*pos == '+')
// 	{
// 		pos++;
// 		val += parse_term();
// 	}
// 	return (val);
// }

// int	main(int ac, char **av)
// {
// 	int	result;

// 	if (ac != 2 || av[1][0] == '\0')
// 		return (1);
// 	pos = av[1];
// 	result = parse_expr();
// 	if (*pos != '\0')
// 		error(*pos);
// 	printf("%d\n", result);
// 	return (0);
// }
