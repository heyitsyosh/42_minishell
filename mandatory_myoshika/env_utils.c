/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 22:31:32 by myoshika          #+#    #+#             */
/*   Updated: 2022/12/16 21:13:12 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*get_env(char *var, t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(var, env->id))
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

void	node_add_back(t_env *envp, t_env *new_node)
{
	if (envp == new_node)
		return ;
	while (envp->next)
		envp = envp->next;
	envp->next = new_node;
	new_node->prev = envp;
}

t_env	*make_node(char	*envp)
{
	t_env	*new_node;
	char	*ptr_to_equal_sign;

	ptr_to_equal_sign = ft_strchr(envp, '=');
	if (!ptr_to_equal_sign)
		return (NULL);
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->id = ft_substr(envp, 0, ptr_to_equal_sign - envp);
	new_node->str = ft_strdup(ptr_to_equal_sign + 1);
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}
