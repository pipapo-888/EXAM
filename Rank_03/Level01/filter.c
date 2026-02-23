// filter:
// Allowed functions: read, strlen, malloc, calloc, realloc, free, printf,
perror
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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFSIZE 100000

	char *
	read_line(void)
{
	int		read_line;
	char	*buf;

	buf = malloc(BUFSIZE + 1);
	read_line = 1;
	while (read_line > 0)
	{
		read_line = read(0, buf, BUFSIZE);
		if (read_line = -1)
			write(2, "Error:", 6);
		buf[read_line] = '\0';
	}
	// read(0, buf, BUFSIZE);
}

int	main(int argc, char **argv)
{
	char *str;

	if (argc != 2 || argv[1][0] == '\0')
	{
		write(2, "Error: 1 Argument Only", 10);
		return (1);
	}

	// while (read(0, &c, 1) > 0)
	// 	write(1, &c, 1);
	// printf("%s\n", str);
	return (0);
}