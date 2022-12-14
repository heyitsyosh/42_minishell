/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 22:31:32 by myoshika          #+#    #+#             */
/*   Updated: 2022/12/22 23:21:54 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*get_env(char *id, t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(id, env->id))
			return (env);
		env = env->next;
	}
	return (env);
}

void	free_envs(t_env *env)
{
	t_env	*node_to_free;

	while (env)
	{
		node_to_free = env;
		free(env->id);
		free(env->str);
		env = env->next;
		free(node_to_free);
	}
}

void	env_add_back(t_env *envp, t_env *env_to_add)
{
	if (envp == env_to_add || !envp || !env_to_add)
		return ;
	while (envp->next)
		envp = envp->next;
	envp->next = env_to_add;
	env_to_add->prev = envp;
}

t_env	*make_env_node(char	*envp)
{
	t_env	*new_node;
	char	*ptr_to_equal_sign;

	ptr_to_equal_sign = ft_strchr(envp, '=');
	if (!ptr_to_equal_sign)
		return (NULL);
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		exit(EXIT_FAILURE);
	new_node->id = ft_substr(envp, 0, ptr_to_equal_sign - envp);
	new_node->str = ft_strdup(ptr_to_equal_sign + 1);
	if (!new_node->id || !new_node->str)
		exit(EXIT_FAILURE);
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

char	**env_list_to_dbl_ptr(t_minishell *m)
{
	t_env	*envp;
	char	*joined;
	char	**ret;

	joined = ft_strdup("");
	envp = m->envp_head;
	while (envp)
	{
		joined = ft_strjoin_with_free(joined, envp->id, FREE_FIRST_PARAM);
		joined = ft_strjoin_with_free(joined, "=", FREE_FIRST_PARAM);
		joined = ft_strjoin_with_free(joined, envp->str, FREE_FIRST_PARAM);
		joined = ft_strjoin_with_free(joined, "\n", FREE_FIRST_PARAM);
		envp = envp->next;
	}
	ret = ft_split(joined, '\n');
	if (!ret)
		exit(EXIT_FAILURE);
	free(joined);
	return (ret);
}
