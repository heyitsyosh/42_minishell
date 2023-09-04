/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 22:54:02 by myoshika          #+#    #+#             */
/*   Updated: 2023/09/04 22:25:46 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/ft_printf.h"
#include "../../includes/libft.h"
#include <string.h> //strerror
#include <errno.h> //errno
#include <stdlib.h> //free
#include <unistd.h> //chdir

bool	expand_to_home(t_token *dir)
{
	if (!dir)
		return (true);
	if (!ft_strcmp(dir->word, "~") || !ft_strncmp(dir->word, "~/", 2))
		return (true);
	return (false);
}

static char	*get_path(t_token *args, t_env *envp)
{
	char	*path;
	t_env	*home;

	home = get_env("HOME", envp);
	if (!home)
	{
		ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
		return (NULL);
	}
	if (!args)
		path = x_strdup(home->str);
	else
		path = ft_strjoin(home->str, (args->word) + 1);
	if (!path)
		print_error_and_exit("strjoin failure");
	return (path);
}

static void	update_oldpwd(t_data *d)
{
	t_env	*oldpwd;
	char	*to_be_oldpwd;

	oldpwd = get_env("OLDPWD", d->envp);
	if (!oldpwd)
		oldpwd = make_env_node("OLDPWD=");
	to_be_oldpwd = x_strdup(d->pwd);
	replace_env_str(oldpwd, to_be_oldpwd);
}

int	builtin_cd(t_token *args, t_data *d)
{
	char	*path;

	if (args && args->next)
		print_error_and_exit("cd: too many arguments\n");
	if (expand_to_home(args))
		path = get_path(args, d->envp);
	else
		path = x_strdup(args->word);
	if (chdir(path) == -1)
	{
		ft_dprintf(STDERR_FILENO, "cd: %s: %s\n", path, strerror(errno));
		free(path);
		return (EXIT_FAILURE);
	}
	update_oldpwd(d);
	// update_pwd(path, args, d);
	free(path);
	return (EXIT_SUCCESS);
}
