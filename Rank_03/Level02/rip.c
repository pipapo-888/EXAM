#include <stdio.h>
#include <string.h>

typedef struct s_node
{
	int	left;
	int	right;
}		t_node;

t_node	check_str(char *str)
{
	ssize_t	len;
	t_node	size;

	size.left = 0;
	size.right = 0;
	len = strlen(str);
	for (int i = 0; i < len; i++)
	{
		if (str[i] == '(')
			size.left++;
		if (str[i] == ')')
			size.right++;
	}
	return (size);
}

int	main(int ac, char **argv)
{
	if (ac != 2)
	{
		printf("ac \n");
		return (1);
	}
	char *str = argv[1];
	t_node size = check_str(str);

	printf("%d %d", size.left, size.right);

	return (0);
}