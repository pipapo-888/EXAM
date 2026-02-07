#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define BUFSIZE 100000

int main(int argc, char **argv)
{
	char *buf;
	char *str = argv[1];
	char c;

	if (argc != 2 || argv[1][0] == '\0')
	{
		write(2, "Error: sss", 10);
		return (1);
	}
	buf = malloc(BUFSIZE + 1);
	// read(0, buf, BUFSIZE);
	while (read(0, &c, 1) > 0)
		write(1, &c, 1);
	printf("%s\n", str);
	return (0);
}