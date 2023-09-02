/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_nonbuiltin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 05:11:38 by myoshika          #+#    #+#             */
/*   Updated: 2023/09/03 07:55:14 by myoshika         ###   ########.fr       */
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

#include <stdio.h>

static char	*get_path_str(t_env *envp)
{
	t_env	*path_env;

	path_env = get_env("PATH", envp);
	if (!path_env)
		return (NULL);
	return (path_env->str);
}

static char	*get_filepath(char *to_execute, t_env *envp)
{
	char	*path;
	char	*end;
	char	*pathname;

	pathname = NULL;
	path = get_path_str(envp);
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

static void	exec_execve(char *pathname, char **argv, char **envp, t_data *d)
{
	execve(pathname, argv, envp);
	if (errno)
	{
		msg_to_stderr(argv[0], ": ", strerror(errno));
		ft_putstr_fd("\n", STDERR_FILENO);
		d->exit_status = 126;
		if (errno == ENOENT)
			d->exit_status = 127;
	}
}

static void	check_filepath(char *filepath, char *to_execute, t_env *envp)
{
	struct stat	info;
	t_env		*path_env;

	path_env = get_env("PATH", envp);
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

void	exec_nonbuiltin(t_token *cmd_list, t_data *d)
{
	char			*filepath;
	char			**argv;
	char			**envp;

	argv = make_argv_from_list(cmd_list);
	envp = make_envp_from_list(d);
	if (!ft_strchr(argv[0], '/'))
		filepath = get_filepath(argv[0], d->envp);
	else
		filepath = x_strdup(argv[0]);
	check_filepath(filepath, argv[0], d->envp);
	exec_execve(filepath, argv, envp, d);
	free_dbl_ptr(argv);
	free_dbl_ptr(envp);
	free(filepath);
}
