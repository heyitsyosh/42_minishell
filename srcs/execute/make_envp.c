/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 03:11:19 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/22 05:40:06 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"
#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include <stdlib.h> //malloc

static size_t	count_malloc_size(t_env *env_list)
{
	size_t	size;

	size = 0;
	while (env_list)
	{
		size++;
		env_list = env_list->next;
	}
	return (size);
}

static void	env_list_to_dbl_ptr(char **envp, t_env *env_list)
{
	size_t	i;

	i = 0;
	while (env_list)
	{
		*(envp + i) = ft_strdup(env_list->id);
		if (!*(envp + i))
			print_error_and_exit("strdup failure");
		*(envp + i) = ft_strjoin_with_free(*(envp + i), "=", FREE_FIRST_PARAM);
		*(envp + i) = ft_strjoin_with_free(*(envp + i), env_list->str, \
			FREE_FIRST_PARAM);
		if (!*(envp + i))
			print_error_and_exit("strjoin failure");
		i++;
		env_list = env_list->next;
	}
	*(envp + i) = NULL;
}

char	**make_envp_from_list(t_env *env_list)
{
	char	**envp;
	size_t	malloc_size;

	if (!env_list)
		return (NULL);
	envp = (char **)malloc(count_malloc_size(env_list) + 1);
	if (!envp)
		print_error_and_exit("malloc failure");
	env_nodes_to_dbl_ptr(envp, env_list);
	return (envp);
}
