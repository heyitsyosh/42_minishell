/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 22:54:02 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/14 02:38:43 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include <string.h> //strerror
#include <errno.h> //errno
#include <stdlib.h> //free
#include <unistd.h> //chdir

static int	get_path(t_token *args)
{
	char	*path;
	t_env	*home;

	home = get_env("HOME");
	if (!home)
	{
		ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (!args)
		path = ft_strdup(home->str);
	else
		path = ft_strjoin(home->str, (args->str) + 2);
	return (path);
}

static void	update_pwd_oldpwd(char *to_be_pwd)
{
	t_env	*pwd;
	t_env	*oldpwd;
	char	*to_be_oldpwd;

	pwd = get_env("PWD", g_ms.envp_head);
	if (pwd)
	{
		to_be_oldpwd = pwd->str;
		replace_env_str(pwd, ft_strdup(to_be_pwd));
		if (!pwd->str)
			print_error_and_exit("strdup failure");
	}
	oldpwd = get_env("OLDPWD", g_ms.envp_head);
	if (oldpwd)
		replace_env_str(oldpwd, to_be_old_pwd);
	free(g_ms.pwd)
	g_ms.pwd = to_be_pwd;
}

int	builtin_cd(t_token *args)
{
	char	*path;

	if (args && args->next)
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (!args || ft_strcmp(args->word, "~/"))
		path = get_path(args);
	else
		path = ft_strdup(args->word);
	if (!path)
		print_error_and_exit("malloc failure");
	if (chdir(path) == -1)
	{
		msg_to_stderr("cd: ", path, strerror(errno));
		ft_putstr_fd("\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	update_pwd_oldpwd(path);
	return (EXIT_SUCCESS);
}
