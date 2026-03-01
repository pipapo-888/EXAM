// filter:
// Allowed functions: read, strlen, malloc, calloc, realloc, free, printf, perror
// ------------------------------------------------------------------------------

// Write a programm taht will take one and only one argument s.

// Your programm will then read from stdin and write all the content read in stdout
// except that every occurence of s must be replaced by '*'.

// For example :

// ./filter bonjour
// will behave the same way as:
// sed 's/bonjour/*******/g'

// in case of error during read or a malloc you must write "Error: " followed by
// the error message in stderr and return 1.

// $> echo 'abcdefgaaaabcdefabc' | ./filter abc | cat -e
// ***defgaaa***def***

// If the program is called whitout argument or with an empty argument or with
// multiples arguments it must return 1.

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFSIZE 10



// int ft_strlen(char *str)
// {
// 	int i = 0;

// 	while(str[i])
// 		i++;
// 	return(i);
// }

// char *ft_strdup(char *str)
// {
// 	if (!str)
// 		return (NULL);
// 	int len = ft_strlen(str);

// 	char *dest = malloc(sizeof(char) * (len + 1));
// 	for (int i = 0; i < len; i++)
// 		dest[i] = str[i];
// 	dest[len] = '\0';
// 	return (dest);
// }

// char	*ft_strjoin(char *s1, char *s2)
// {
// 	char	*dest;
// 	int		i;
// 	int		j;

// 	if (!s1 || !s2)
// 		return (NULL);
// 	dest = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
// 	if (dest == NULL)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	while (s1[i])
// 	{
// 		dest[i] = s1[i];
// 		i++;
// 	}
// 	while (s2[j])
// 	{
// 		dest[i + j] = s2[j];
// 		j++;
// 	}
// 	dest[i + j] = '\0';
// 	return (dest);
// }


// 	char *read_line(void)
// {
// 	int		read_line;
// 	char	*buf;
// 	char	*str = NULL;
// 	char	*tmp = ft_strdup("");

// 	buf = malloc(BUFSIZE + 1);
// 	if (buf == NULL)
// 		return (NULL);
// 	read_line = 1;
// 	while (read_line > 0)
// 	{
// 		read_line = read(0, buf, BUFSIZE);
// 		if (read_line == -1)
// 		{	
// 			perror("Error:");
// 			return (NULL);
// 		}
// 		buf[read_line] = '\0';

// 		str = ft_strjoin(tmp, buf);
// 		free(tmp);
// 		tmp = str;
// 	}
// 	return (str);
// }

int ft_strlen(char *str)
{
	int len = 0;

	while (str[len])
		len++;
	return (len);
}

char *read_line(void)
{
	char	*str;
	char	buf[BUFSIZE];
	size_t	len = 0;
	int readline = 1;
	
	str = malloc(1);
	str[0] = '\0';
	while(readline > 0)
	{
		readline = read(0, buf, BUFSIZE);
		if (readline == -1)
			return (perror("Error:"),NULL);		
		char *tmp = realloc(str, len + readline + 1);
		if (tmp == NULL)
			return (free(str), NULL);
		str = tmp;
		for (int i = 0; i < readline; i++)
			str[len + i] = buf[i];
		len += readline;
		str[len] = '\0';
	}
	return (str);
}



int	main(int argc, char **argv)
{
	char *str;
	char *bug;
	char *ans;
	if (argc != 2 || argv[1][0] == '\0')
	{
		write(2, "Error: 1 Argument Only", 22);
		return (1);
	}
	str = read_line();
	if (str == NULL)
	{
		write(1, "Error", 5);
		return (1);
	}
	bug = argv[1];
	ans = str;

	while ((str = memmem(str, ft_strlen(str), bug, ft_strlen(bug))))
	{
		for (int i = 0; i < ft_strlen(bug); i++)
			str[i] = '*';
	}
	
	printf("%s", ans);

	free(ans);
	return (0);
}