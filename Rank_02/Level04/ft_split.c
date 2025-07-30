#include <stdio.h>
#include <stdlib.h>

int ft_is_space(int c)
{
	if (c == '\n' || c == ' ' || c == '\t')
		return (1);
	return (0);
}

int ft_count_words(char *str)
{
	int word_count = 0;
	int new_word = 0;

	while(*str)
	{
		if (ft_is_space(*str))
			new_word = 0;
		else if (!new_word)
		{
			word_count++;
			new_word = 1;
		}
		str++;
	}
	return (word_count);
}

char *ft_strndup(char *str, int len)
{
	int i = 0;
	char *word = malloc(len + 1);
	if (!word)
		return (NULL);

	while (len > i && str[i])
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char *str)
{
	char **result;
	int word_count;
	int i = 0;
	int len;

	word_count = ft_count_words(str);
	result = malloc((word_count + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	while (*str)
	{
		while (*str && ft_is_space(*str))
			str++;
		if (*str)
		{
			char *string = str;
			len = 0;
			while (*str && !ft_is_space(*str))
			{
				len++;
				str++;
			}
			result[i++] = ft_strndup(string, len);
		}
	}
	result[i] = NULL;
	return (result);
}

int main()
{
	char str[] = "    Hello World My Name is  dddd\tfffff  dasfalfk  ";
	char **result;
	int i = 0;

	result = ft_split(str);
	while (result[i])
	{
		printf("%s\n", result[i]);
		i++;
	}
	return (0);
}
