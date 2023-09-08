/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 22:54:02 by myoshika          #+#    #+#             */
/*   Updated: 2023/09/08 15:42:40 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"
#include "../../includes/minishell.h"
#include "../../includes/ft_printf.h"
#include "../../includes/libft.h"
#include <string.h> //strerror
#include <errno.h> //errno
#include <stdlib.h> //free
#include <unistd.h> //chdir

static void	update_pwd(char *newpwd, t_data *d)
{
	t_env	*pwd;

	free(d->pwd);
	d->pwd = newpwd;
	pwd = get_env("PWD", d->envp);
	if (!pwd)
	{
		pwd = make_env_node("PWD=");
		env_add_back(d->envp, pwd);
	}
	replace_env_str(pwd, x_strdup(newpwd));
}

static void	update_oldpwd(t_data *d)
{
	t_env	*oldpwd;
	char	*new_oldpwd;

	new_oldpwd = x_strdup(d->pwd);
	oldpwd = get_env("OLDPWD", d->envp);
	if (!oldpwd)
	{
		oldpwd = make_env_node("OLDPWD=");
		env_add_back(d->envp, oldpwd);
	}
	replace_env_str(oldpwd, new_oldpwd);
}

static char	*expand_home(t_token *args, t_env *envp)
{
	char	*path;
	t_env	*home;

	home = get_env("HOME", envp);
	if (!home)
	{
		ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
		return (NULL);
	}
	path = x_strdup(home->str);
	if (args)
		path = x_strjoin_free(path, args->word + 1, FREE_FIRST);
	if (!path)
		print_error_and_exit("strjoin failure");
	return (path);
}

char	*get_chdir_path(t_token *args, t_data *d)
{
	if (!args || \
		!ft_strcmp(args->word, "~") || !ft_strncmp(args->word, "~/", 2))
		return (expand_home(args, d->envp));
	else
		return (x_strdup(args->word));
}

int	builtin_cd(t_token *args, t_data *d)
{
	char	*path;
	char	*newpwd;

	if (args && args->next)
	{
		ft_dprintf(STDERR_FILENO, "cd: too many arguments\n");
		return (EXIT_FAILURE);
	}
	path = get_chdir_path(args, d);
	if (!path || chdir(path) == -1)
	{
		if (path)
			ft_dprintf(STDERR_FILENO, "cd: %s: %s\n", path, strerror(errno));
		free(path);
		return (EXIT_FAILURE);
	}
	update_oldpwd(d);
	newpwd = make_pwd_path(path, d->pwd);
	update_pwd(newpwd, d);
	free(path);
	return (EXIT_SUCCESS);
}
