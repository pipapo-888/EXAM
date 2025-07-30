#include <stdlib.h>
#include <stdio.h>

int ft_strlen(char *str)
{
	int len = 0;

	while (str[len])
		len++;
	return (len);
}

char *ft_strdup(char *src)
{
	int len = ft_strlen(src);
	char *dest = malloc(len + 1);
	if (!dest)
		return (NULL);
	int i = 0;
	while (len--)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int main()
{
	char *str = "Hello world";
	char *dest = ft_strdup(str);
	printf("%s,  %s", dest, str);


	return (0);
}
