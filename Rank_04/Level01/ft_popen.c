
// Assignment name  : ft_popen
// Expected files   : ft_popen.c
// Allowed functions: pipe, fork, dup2, execvp, close, exit
// --------------------------------------------------------------------------------------

// Write the following function:

// int ft_popen(const char *file, char *const argv[], char type);

// The function must launch the executable file with the arguments argv (using execvp).
// If type is 'r' the function must return a file descriptor connected to the output of the command.
// If type is 'w' the function must return a file descriptor connected to the input of the command.
// In case of error or invalid parameter the function must return -1.

// For example, the function could be used like that:

// int main()
// {
//     int  fd;
//     char *line;

//     fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
//     while ((line = get_next_line(fd)))
//         ft_putstr(line);
//     return (0);
// }


// int	main() {
// 	int	fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
// 	dup2(fd, 0);
// 	fd = ft_popen("grep", (char *const []){"grep", "c", NULL}, 'r');
// 	char	*line;
// 	while ((line = get_next_line(fd)))
// 		printf("%s", line);
// }


// Hints:
// Do not leak file descriptors!
// This exercise is inspired by the libc's popen().



#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int ft_popen(const char *file, char *const argv[], char type)
{
	int fd[2];
	pipe(fd);

	__pid_t pid;
	
	if (type == 'r')
	{
		pid = fork();
		if (pid == 0)
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
			execvp(file, argv);
			exit(-1);
		}
		close(fd[1]);
		return(fd[0]);
	}
	if (type == 'w')
	{
		pid = fork();
		if (pid == 0)
		{
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			close(fd[1]);
			execvp(file, argv);
			exit(-1);
		}
		close(fd[0]);
		return (fd[1]);
	}
	return -1;
}

int	main() {
	char *str[] = {"ls", NULL};
	int	fd = ft_popen("ls", str, 'r');

	char str2[1000];
	int len = read(fd, str2, 1000);
	str2[len] = '\0';

	printf("%s", str2);

	
	char *str3[] = {"grep","ll", NULL};
	fd = ft_popen("grep", str3, 'w');

	write(fd, "hello\nWorld\n", 12);

	close(fd);
}