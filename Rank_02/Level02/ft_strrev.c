#include <stdio.h>


int ft_strlen(char *str)
{
	int len = 0;

	while (str[len])
		len++;
	return(len);
}
char *ft_strrev(char *str)
{
	int i = 0;
	char *temp = str;
	char tmp;

	int len = ft_strlen(str);

	len -= 1;
	while (i < len)
	{
		tmp = str[i];
		str[i] = temp[len];
		temp[len] = tmp;
		i++;
		len--;
	}


	return (str);
}

int main()
{
	char str[] = "Hello oLLEH";
	printf("%s\n", str);
	ft_strrev(str);

	printf("%s\n", str);
	return (0);
}
