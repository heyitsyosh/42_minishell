/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 22:54:02 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/23 13:38:44 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include <string.h> //strerror
#include <errno.h> //errno
#include <stdlib.h> //free
#include <unistd.h> //chdir

static char	*get_path(t_token *args)
{
	char	*path;
	t_env	*home;

	home = get_env("HOME");
	if (!home)
	{
		ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
		return (NULL);
	}
	if (!args)
		path = xstrdup(home->str);
	else
		path = ft_strjoin(home->str, (args->word) + 1);
	if (!path)
		print_error_and_exit("strjoin failure");
	return (path);
}

static void	update_oldpwd(void)
{
	t_env	*oldpwd;
	char	*to_be_oldpwd;

	oldpwd = get_env("OLDPWD");
	if (!oldpwd)
		oldpwd = make_env_node("OLDPWD=");
	to_be_oldpwd = xstrdup(g_ms.pwd);
	replace_env_str(oldpwd, to_be_oldpwd);
}

static void	update_pwd(char *to_be_pwd)
{
	t_env	*pwd;

	pwd = get_env("PWD");
	if (!pwd)
		pwd = make_env_node("PWD=");
	replace_env_str(pwd, xstrdup(to_be_pwd));
	free(g_ms.pwd);
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
	if (!args || !ft_strcmp(args->word, "~") \
		|| !ft_strncmp(args->word, "~/", 2))
		path = get_path(args);
	else
		path = xstrdup(args->word);
	if (chdir(path) == -1)
	{
		msg_to_stderr("cd: ", path, ": ");
		msg_to_stderr(strerror(errno), "\n", NULL);
		free(path);
		return (EXIT_FAILURE);
	}
	update_oldpwd();
	update_pwd(path);
	return (EXIT_SUCCESS);
}
