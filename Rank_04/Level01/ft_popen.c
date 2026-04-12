#include <stdio.h>

// void *ft_popen(const char *command, const char *type)
// {




// 	return 
// }

// int ft_popen(const char *file, char *const argv[], char type)
// {



// }

int	main() {
	int	fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
	dup2(fd, 0);
	fd = popen("grep", (char *const []){"grep", "c", NULL}, 'r');
	char	*line;
// 	while ((line = get_next_line(fd)))
// 		printf("%s", line);
}