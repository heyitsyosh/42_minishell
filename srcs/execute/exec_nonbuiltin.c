/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_nonbuiltin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 05:11:38 by myoshika          #+#    #+#             */
/*   Updated: 2023/08/24 04:44:39 by myoshika         ###   ########.fr       */
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
#include <sys/stat.h> //stat, S_ISDIR
#include <sys/wait.h> //wait

static char	*get_path_str(void)
{
	t_env	*path_env;

	path_env = get_env("PATH");
	if (!path_env)
		return (NULL);
	return (path_env->str);
}

static char	*get_filepath(char *to_execute)
{
	char	*path;
	char	*end;
	char	*pathname;

	pathname = NULL;
	path = get_path_str();
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
		if (access(pathname, F_OK) == 0)
			return (pathname);
		else if (!end)
			break ;
		free(pathname);
		path = end + 1;
	}
	return (pathname);
}

static void	exec_execve(char *pathname, char **argv, char **envp)
{
	execve(pathname, argv, envp);
	if (errno)
	{
		msg_to_stderr(argv[0], ": ", strerror(errno));
		ft_putstr_fd("\n", STDERR_FILENO);
		g_ms.exit_status = 126;
		if (errno == ENOENT)
			g_ms.exit_status = 127;
	}
}

static void	check_filepath(char *filepath, char *to_execute)
{
	struct stat	info;
	t_env		*path_env;

	path_env = get_env("PATH");
	if (!path_env || *(path_env->str) == '\0')
	{
		msg_to_stderr(to_execute, ": ", "No such file or directory\n");
		exit (127);
	}
	if (!filepath \
		|| !ft_strcmp(to_execute, "") \
		|| !ft_strcmp(to_execute, "..") \
		|| access(filepath, F_OK) == -1)
	{
		msg_to_stderr(to_execute, ": ", "command not found\n");
		exit (127);
	}
	stat(filepath, &info);
	if (S_ISDIR(info.st_mode))
	{
		msg_to_stderr(to_execute, ": ", "Is a directory\n");
		exit (126);
	}
}

void	exec_nonbuiltin(t_token *cmd_list)
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
	check_filepath(filepath, argv[0]);
	exec_execve(filepath, argv, envp);
	free(filepath);
	free_dbl_ptr(argv);
	free_dbl_ptr(envp);
}
