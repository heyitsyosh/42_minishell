/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 22:54:02 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/13 04:56:31 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <string.h> //strerror
#include <errno.h> //errno

int	cd_with_no_args(void)
{
	t_env	*home;

	home = getenv("HOME");
	if (!home)
	{
		ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	
}

// get_chdir_destination(t_token *args)

char	*get_relative_path(char	*given)
{
	
}

void	update_pwd_oldpwd(char *to_be_pwd)
{
	t_env	*pwd;
	t_env	*oldpwd;
	char	*to_be_oldpwd;

	pwd = get_env("PWD", g_ms.envp_head);
	if (pwd)
	{
		to_be_oldpwd = pwd->str;
		pwd->str = to_be_pwd;
	}
	free(g_ms.pwd)
	g_ms.pwd = ft_strdup(to_be_pwd);
	if (!g_ms.pwd)
		print_error_and_exit("strdup failure");
	oldpwd = get_env("OLDPWD", g_ms.envp_head);
	if (oldpwd)
	{
		free(oldpwd->word);
		oldpwd->word = to_be_oldpwd;
	}
}

int	builtin_cd(t_token *args)
{
	char	*path;

	if (args && args->next)
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (args && *args->word == '/')
		path = args->word;
	else
		path = get_relative_path(args);
	if (chdir(path) == -1)
	{
		msg_to_stderr("cd: ", strerror(errno), "\n")
		return (EXIT_FAILURE);
	}
	update_pwd_oldpwd(path);
	return (EXIT_SUCCESS);
}

//chdir segfault??
//delete directory and, ENV kakikaeru junban
//no args
//~
//no $HOME?
//rewrite env oldpwd, pwd
//shell vars vs env vars