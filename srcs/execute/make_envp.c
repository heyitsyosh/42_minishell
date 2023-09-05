/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 22:09:23 by myoshika          #+#    #+#             */
/*   Updated: 2023/09/06 00:36:52 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"
#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include <stdlib.h> //malloc

static size_t	count_envs(t_env *envp)
{
	size_t	count;

	count = 0;
	while (envp)
	{
		count++;
		envp = envp->next;
	}
	return (count);
}

static char	*join_envp_line(t_env *envp)
{
	char	*joined;

	joined = x_strdup("");
	joined = x_strjoin_free(joined, envp->id, FREE_FIRST);
	joined = x_strjoin_free(joined, "=", FREE_FIRST);
	joined = x_strjoin_free(joined, envp->str, FREE_FIRST);
	return (joined);
}

char	**make_envp_from_list(t_data *d)
{
	size_t	i;
	t_env	*envp;
	char	**ret;

	ret = (char **)malloc((count_envs(d->envp) + 1) * sizeof(char *));
	if (!ret)
		print_error_and_exit("malloc failure");
	i = 0;
	envp = d->envp;
	while (envp)
	{
		ret[i] = join_envp_line(envp);
		i++;
		envp = envp->next;
	}
	ret[i] = NULL;
	return (ret);
}
