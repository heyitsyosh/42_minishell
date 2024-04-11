/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_ii.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 20:42:50 by myoshika          #+#    #+#             */
/*   Updated: 2024/04/12 04:19:39 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "minishell.h"
#include "libft.h"
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
		split_path++;
	}
	return (newpwd);
}

char	*make_pwd_path(char *chdir_path, char *pwd)
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
	if (*newpwd == '\0')
	{
		free(newpwd);
		newpwd = x_strdup("/");
	}
	return (newpwd);
}
