/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_ii.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 20:42:50 by myoshika          #+#    #+#             */
/*   Updated: 2023/09/06 23:28:40 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"
#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include <stdlib.h> //free

static void	delete_last_elem(char **path)
{
	char	*last_elem;
	char	*updated_path;

	last_elem = ft_strrchr(*path, '/');
	if (!last_elem)
		return ;
	updated_path = ft_substr(*path, 0, last_elem - *path);
	if (!updated_path)
		print_error_and_exit("substr failure");
	free(*path);
	*path = updated_path;
}

static char	*resolve_relative_path(char **split_path, char *newpwd)
{
	while (*split_path && newpwd)
	{
		if (!ft_strcmp(*split_path, "."))
			;
		else if (!ft_strcmp(*split_path, ".."))
			delete_last_elem(&newpwd);
		else
		{
			newpwd = x_strjoin_free(newpwd, "/", FREE_FIRST);
			newpwd = x_strjoin_free(newpwd, *split_path, FREE_FIRST);
		}
		*split_path++;
	}
	return (newpwd);
}

static char	*make_pwd_path(char *chdir_path, char *pwd)
{
	char	**split_path;
	char	*newpwd;

	split_path = ft_split(chdir_path, '/');
	if (!split_path)
		print_error_and_exit("split failure");
	if (*chdir_path == '/' || !ft_strcmp(pwd, "/"))
		newpwd = x_strdup("");
	else
		newpwd = x_strdup(pwd);
	newpwd = resolve_relative_path(split_path, newpwd);
	free_dbl_ptr(split_path);
	return (newpwd);
}

void	update_pwd(char *chdir_path, t_data *d)
{
	t_env	*pwd;
	char	*newpwd;

	newpwd = make_pwd_path(chdir_path, d->pwd);
	if (*newpwd == '\0')
	{
		free(newpwd);
		newpwd = x_strdup("/");
	}
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
