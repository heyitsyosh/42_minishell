/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 05:11:38 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/24 18:33:28 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"
#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include <unistd.h> //access, fork, execve, X_OK
#include <stdlib.h> //free, EXIT_SUCCESS
#include <string.h> //strerror
#include <errno.h> //errno
#include <sys/types.h> //pid_t
#include <sys/wait.h> //wait

static char	*get_path_str(t_env *env)
{
	if (!env)
		return (NULL);
	return (env->str);
}

static char	*get_filepath(char *to_execute)
{
	char	*path;
	char	*end;
	char	*pathname;

	path = get_path_str(get_env("PATH"));
	while (path)
	{
		end = ft_strchr(path, ':');
		if (end)
			pathname = ft_substr(path, 0, end - path);
		else
			pathname = ft_strdup(path);
		pathname = ft_strjoin_with_free(pathname, "/", FREE_FIRST_PARAM);
		pathname = ft_strjoin_with_free(pathname, to_execute, FREE_FIRST_PARAM);
		if (!pathname)
			print_error_and_exit("malloc failure");
		if (access(pathname, F_OK) == 0) //investigate F_OK, isdir, X_OK
			return (pathname);
		else if (!end)
			break ;
		free(pathname);
		path = end + 1;
	}
	return (pathname);
}

static void	execve_func(char *pathname, char **argv, char **envp)
{
	execve(pathname, argv, envp);
	if (errno)
	{
		msg_to_stderr(argv[0], ": ", strerror(errno));
		ft_putstr_fd("\n", STDERR_FILENO);
	}
}

void	exec_execve(t_token *cmd_list)
{
	char	*filepath;
	char	**argv;
	char	**envp;

	argv = make_argv_from_list(cmd_list);
	envp = make_envp_from_list();
	if (!ft_strchr(argv[0], '/'))
		filepath = get_filepath(argv[0]);
	else
		filepath = x_strdup(argv[0]);
	// {
	printf("[%s]", filepath);
	fflush(stdout);
	execve_func(filepath, argv, envp);
	// }
	free(filepath);
	free_dbl_ptr(argv);
	free_dbl_ptr(envp);
}

void	exec_nonbuiltin(t_ast *cmd)
{
	pid_t	pid;
	int		wait_status;

	pid = fork();
	if (pid == -1)
		print_error_and_exit("fork failure");
	else if (pid == 0)
	{
		// open_redir_files(cmd->redir);
		// set_up_redirect(cmd->redir);
		exec_execve(cmd->cmd_list);
		// reset_redirect(cmd->redir);
	}
	else
		wait(&wait_status);
}

//investigate exit status. and error messages (no valid filepath = 127)