// Assignment name:	picoshell
// Expected files:		picoshell.c
// Allowed functions:	close, fork, wait, exit, execvp, dup2, pipe
// ___________________________________________________________________

// Write the following function:

// int    picoshell(char **cmds[]);

// The goal of this function is to execute a pipeline. It must execute each
// commands of cmds and connect the output of one to the input of the
// next command (just like a shell).
// e
// Cmds contains a null-terminated list of valid commands. Each rows
// of cmds are an argv array directly usable for a call to execvp. The first
// arguments of each command is the command name or path and can be passed
// directly as the first argument of execvp.

// If any error occur, The function must return 1 (you must of course
// close all the open fds before). otherwise the function must wait all child
// processes and return 0. You will find in this directory a file main.c which
// contain something to help you test your function.


// Examples: 
// ./picoshell /bin/ls "|" /usr/bin/grep picoshell
// picoshell
// ./picoshell echo 'squalala' "|" cat "|" sed 's/a/b/g'
// squblblb

// ___________________________________________________________________

// Old summary by a student:
// You are given a main function. It converts received arguments into cmds array
// of strings. When there is a pipe the commands after the pipe are in the next
// array of strings. You have to create a pipeline using the cmds you receive from
// the main, and execute them. If there is any error the function should return 1.
// Close all FFS before returning. If the cmds executed successfully wait all
// child processes and return 0.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int picoshell(char **cmds[])
{
	int i = 0;
	int prev_fd = -1



}





// int picoshell(char **cmds[])
// {
// 	int i = 0;
// 	int prev_fd = -1;
// 	int fd[2];
	
// 	if (!cmds || !cmds[0])
// 		return (0);
// 	while (cmds[i])
// 	{
// 		int has_next = (cmds[i + 1] != NULL);
// 		if (has_next)
// 			if (pipe(fd) == -1)	return 1;

// 		pid_t pid = fork();
// 		if (pid < 0) return 1;
// 		if (pid == 0)
// 		{
// 			if (prev_fd != -1)
// 			{
// 				dup2(prev_fd, 0);
// 				close(prev_fd);
// 			}
// 			if (has_next)
// 			{
// 				dup2(fd[1], 1);
// 				close(fd[0]);
// 				close(fd[1]);
// 			}
// 			execvp(cmds[i][0], cmds[i]);
// 			exit(1);
// 		}
// 		if (prev_fd != -1) 
// 			close(prev_fd);
// 		if (has_next)
// 		{
// 			close(fd[1]);
// 			prev_fd = fd[0];
// 		}
// 		i++;
// 	}
// 	while (wait(NULL) > 0)
// 		;
// 	return (0);
// }




int main(int argc, char **argv)
{
	char	**cmds[argc + 1];
	int		ncmds = 0;
	int		start = 1;
	int		i;

	for (i = 1; i <= argc; i++)
	{
		if (i == argc || strcmp(argv[i], "|") == 0)
		{
			int len = i - start;
			char **cmd = malloc((len + 1) * sizeof(char *));
			int j;
			for (j = 0; j < len; j++)
				cmd[j] = argv[start + j];
			cmd[len] = NULL;
			cmds[ncmds++] = cmd;
			start = i + 1;
		}
	}
	cmds[ncmds] = NULL;

	int ret = picoshell(cmds);
	fprintf(stderr, "picoshell returned: %d\n", ret);
	return ret;
}

// cc picoshell.c -o picoshell
// ./picoshell echo hello "|" cat
// ./picoshell echo squalala "|" cat "|" sed 's/a/b/g'
// ./picoshell ls "|" grep picoshell