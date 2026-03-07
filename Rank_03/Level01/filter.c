// filter:
// Allowed functions: read, strlen, malloc, calloc, realloc, free, printf
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
#include <string.h>
#include <unistd.h>

#define BUFSIZE 10

// char *read_line(void)
// {
// 	char	*str;
// 	char	buf[BUFSIZE];
// 	size_t	len = 0;
// 	int readline = 1;

// 	str = malloc(1);
// 	str[0] = '\0';
// 	while(readline > 0)
// 	{
// 		readline = read(0, buf, BUFSIZE);
// 		if (readline == -1)
// 			return (perror("Error:"),NULL);
// 		char *tmp = realloc(str, len + readline + 1);
// 		if (tmp == NULL)
// 			return (free(str), NULL);
// 		str = tmp;
// 		for (int i = 0; i < readline; i++)
// 			str[len + i] = buf[i];
// 		len += readline;
// 		str[len] = '\0';
// 	}
// 	return (str);
// }

// int	main(int argc, char **argv)
// {
// 	char *str;
// 	char *bug;
// 	char *ans;
// 	if (argc != 2 || argv[1][0] == '\0')
// 	{
// 		write(2, "Error: 1 Argument Only", 22);
// 		return (1);
// 	}
// 	str = read_line();
// 	if (str == NULL)
// 	{
// 		write(1, "Error", 5);
// 		return (1);
// 	}
// 	bug = argv[1];
// 	ans = str;

// 	while ((str = memmem(str, ft_strlen(str), bug, ft_strlen(bug))))
// 	{
// 		for (int i = 0; i < ft_strlen(bug); i++)
// 			str[i] = '*';
// 	}

// 	printf("%s", ans);

// 	free(ans);
// 	return (0);
// }

char	*read_str(void)
{
	char	*str;
	ssize_t	readline_ret;
	ssize_t	str_len;
	char	*tmp;

	str = malloc(1);
	str_len = 0;
	while (1)
	{
		readline_ret = read(0, str + str_len, 1);
		if (readline_ret == 0)
			break ;
		if (readline_ret == -1)
		{
			free(str);
			if (tmp != NULL)
				free(tmp);
			perror("Error");
			return (NULL);
		}
		str_len += readline_ret;
		tmp = realloc(str, str_len + 1);
		if (tmp == NULL)
		{
			free(str);
			perror("Error");
			return (NULL);
		}
		str = tmp;
	}
	str[str_len] = '\0';
	// free(tmp);
	return (str);
}

int	main(int argc, char **argv)
{
	char	*str;
	char	*av;
	char	*ans;

	if (argc != 2 || argv[1][0] == '\0')
		return (1);
	av = argv[1];
	str = read_str();
	if (!str)
		return (1);
	ans = str;
	while ((str = memmem(str, strlen(str), av, strlen(av))))
	{
		for (int i = 0; i < strlen(av); i++)
			str[i] = '*';
	}
	printf("%s", ans);
	free(ans);
	return (0);
}

// int main(int ac, char **av)
// {
// 	if (ac != 2 || av[1][0] == '\0')
// 		return (1);
// 	ssize_t bytes_read = 1, loaded = 0, capacity = BUFSIZ;
// 	char	*buffer = NULL;

// 	while (1)
// 	{
// 		while (capacity <= loaded + BUFSIZ)
// 		{
// 			capacity *= 2;
// 			char *temp = realloc(buffer, capacity + 1);
// 			if (!temp)
// 				return (free(buffer), perror("Error"), 1);
// 			buffer = temp;
// 		}
// 		if (bytes_read == 0)
// 			break ;
// 		if (bytes_read == -1)
// 			return (free(buffer), perror("Error"), 1);
// 		bytes_read = read(0, buffer + loaded, BUFSIZ);
// 		loaded += bytes_read;
// 	}
// 	buffer[loaded] = '\0';
// 	char *found;
// 	char *output = buffer;
// 	char *target = av[1];
// 	size_t target_len = strlen(target);
// 	while ((found = memmem(buffer, loaded - (buffer - output), target,
				target_len)) != NULL)
// 	{
// 		for(int i = 0; i < target_len; i++)
// 			found[i] = '*';
// 		buffer += target_len + (found - buffer);
// 	}
// 	printf("%s", output);
// 	free(output);
// 	return (0);
// }