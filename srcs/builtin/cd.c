/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 22:54:02 by myoshika          #+#    #+#             */
/*   Updated: 2023/09/05 14:55:52 by myoshika         ###   ########.fr       */
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

static void	update_oldpwd(t_data *d)
{
	t_env	*oldpwd;
	char	*new_oldpwd;

	new_oldpwd = x_strdup(d->pwd);
	oldpwd = get_env("OLDPWD", d->envp);
	if (!oldpwd)
		oldpwd = make_env_node("PWD=");
	replace_env_str(oldpwd, new_oldpwd);
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
	path = x_strdup(home->str);
	if (args)
		path = x_strjoin_free(path, args->word + 1, FREE_FIRST_PARAM);
	if (!path)
		print_error_and_exit("strjoin failure");
	return (path);
}

char	*get_chdir_path(t_token *args, t_data *d)
{
	if (!args || \
		!ft_strcmp(args->word, "~") || !ft_strncmp(args->word, "~/", 2))
		return (get_path(args, d->envp));
	else
		return (x_strdup(args->word));
}

int	builtin_cd(t_token *args, t_data *d)
{
	char	*path;

	if (args && args->next)
		print_error_and_exit("cd: too many arguments\n");
	path = get_chdir_path(args, d);
	if (chdir(path) == -1)
	{
		ft_dprintf(STDERR_FILENO, "cd: %s: %s\n", path, strerror(errno));
		free(path);
		return (EXIT_FAILURE);
	}
	update_oldpwd(d);
	update_pwd(path, d);
	free(path);
	return (EXIT_SUCCESS);
}
