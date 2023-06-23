/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 05:11:38 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/23 12:10:40 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"
#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include <unistd.h> //access, execve, X_OK
#include <stdlib.h> //free, EXIT_SUCCESS

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
		if (access(pathname, X_OK) == 0)
			return (pathname);
		else if (!end)
			break ;
		free(pathname);
		path = end + 1;
	}
	return (path);
}

static void	execve_func(char *pathname, char **argv, char **envp)
{
	execve(pathname, argv, envp);
	print_error_and_exit("execve failure");
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
		filepath = xstrdup(argv[0]);
	// {
	execve_func(filepath, argv, envp);
	g_ms.exit_status = EXIT_SUCCESS;
	// }
	free(filepath);
	free_dbl_ptr(argv);
	free_dbl_ptr(envp);
}

//investigate exit status. and error messages (no valid filepath = 127)