#include <stdio.h>

int ft_strlen(char *str)
{
	int len = 0;
	while(str[len])
		len++;
	return (len);
}

int cal(char *s)
{
	int ans = s[0] - '0';
	for (int i = 1; i < ft_strlen(s); i++)
	{
		if (s[i] == '*')
			ans *= s[i + 1] - '0';
	}



}

int main(int ac, char **av)
{
	if (ac != 2 || av[1][0] == '\0')
		return 1;
	
	


	return (0);
}