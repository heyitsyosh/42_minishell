#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void make_eldest(int fd[2], char **envp)
{
	pid_t pid = fork();
	if (pid == 0) //child
	{
		close(fd[0]);
		execve("/bin/ls",  (char *[]){ "ls", NULL }, envp);
	}
}


void	make_youngest(int fd[2], char **envp)
{
	pid_t pid = fork();
	if (pid == 0)
	{
		close(fd[1]);
		execve("/bin/grep",  (char *[]){ "grep", "minishell_", NULL }, envp);
	}
}

int	main(int argc, char **argv, char **envp){
	int fd[2];

	int original_out = dup(STDOUT_FILENO);
	pipe(fd);
	dup2(fd[1], STDOUT_FILENO);
	make_eldest(fd, envp);
	dup2(fd[0], STDIN_FILENO);
	dup2(original_out, STDOUT_FILENO);
	make_youngest(fd, envp);
}
