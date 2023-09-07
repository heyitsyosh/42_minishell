/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_nonbuiltin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 05:11:38 by myoshika          #+#    #+#             */
/*   Updated: 2023/09/07 19:27:36 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"
#include "../../includes/ft_printf.h"
#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include <sys/stat.h> //stat, struct stat, S_ISDIR
#include <unistd.h> //access, execve, F_OK, STDERR_FILENO
#include <stdlib.h> //free, exit
#include <string.h> //strerror
#include <errno.h> //errno, ENOENT

static char	*get_path_str(char *to_execute, t_env *envp)
{
	t_env	*path_env;

	path_env = get_env("PATH", envp);
	if (!path_env || *(path_env->str) == '\0')
	{
		ft_dprintf(STDERR_FILENO, "%s: No such file or directory\n", to_execute);
		exit (127);
	}
	return (path_env->str);
}

static char	*get_filepath(char *to_execute, t_env *envp)
{
	char	*path;
	char	*end;
	char	*pathname;

	pathname = NULL;
	path = get_path_str(to_execute, envp);
	while (path)
	{
		end = ft_strchr(path, ':');
		if (end)
			pathname = ft_substr(path, 0, end - path);
		else
			pathname = ft_strdup(path);
		pathname = x_strjoin_free(pathname, "/", FREE_FIRST);
		pathname = x_strjoin_free(pathname, to_execute, FREE_FIRST);
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
		ft_dprintf(STDERR_FILENO, "%s: %s\n", argv[0], strerror(errno));
		d->exit_status = 126;
		if (errno == ENOENT)
			d->exit_status = 127;
	}
}

static void	check_filepath(char *filepath, char *to_execute)
{
	struct stat	info;

	if (!filepath \
		|| !ft_strcmp(to_execute, "") \
		|| !ft_strcmp(to_execute, "..") \
		|| access(filepath, F_OK) == -1)
	{
		ft_dprintf(STDERR_FILENO, "%s: command not founad\n", to_execute);
		exit (127);
	}
	stat(filepath, &info);
	if (S_ISDIR(info.st_mode))
	{
		ft_dprintf(STDERR_FILENO, "%s: Is a directory\n", to_execute);
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
	check_filepath(filepath, argv[0]);
	exec_execve(filepath, argv, envp, d);
	free_dbl_ptr(argv);
	free_dbl_ptr(envp);
	free(filepath);
}
