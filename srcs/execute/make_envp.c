/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 22:09:23 by myoshika          #+#    #+#             */
/*   Updated: 2023/07/07 22:20:35 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"
#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include <stdlib.h> //malloc

static size_t	count_envs(void)
{
	size_t	count;
	t_env	*envp;

	count = 0;
	envp = g_ms.envp_head;
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
	joined = ft_strjoin_with_free(joined, envp->id, FREE_FIRST_PARAM);
	joined = ft_strjoin_with_free(joined, "=", FREE_FIRST_PARAM);
	joined = ft_strjoin_with_free(joined, envp->str, FREE_FIRST_PARAM);
	if (!joined)
		print_error_and_exit("strjoin failure");
	return (joined);
}

char	**make_envp_from_list(void)
{
	size_t	i;
	t_env	*envp;
	char	**ret;

	ret = (char **)malloc((count_envs() + 1) * sizeof(char *));
	if (!ret)
		print_error_and_exit("malloc failure");
	i = 0;
	envp = g_ms.envp_head;
	while (envp)
	{
		ret[i] = join_envp_line(envp);
		i++;
		envp = envp->next;
	}
	ret[i] = NULL;
	return (ret);
}
