/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 22:31:32 by myoshika          #+#    #+#             */
/*   Updated: 2023/09/03 04:04:20 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"
#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include <stdlib.h> //malloc, free, exit

t_env	*get_env(char *id, t_env *env)
{
	if (!id || !env)
		return (NULL);
	while (env)
	{
		if (!ft_strcmp(id, env->id))
			return (env);
		env = env->next;
	}
	return (env);
}

void	add_new_env(t_env *tmp, t_data *d)
{
	if (!d->envp)
	{
		d->envp = tmp;
		return ;
	}
	env_add_back(d->envp, tmp);
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

void	replace_env_str(t_env *env, char *new_str)
{
	if (!env)
		return ;
	free(env->str);
	env->str = new_str;
}

t_env	*make_env_node(char	*envp)
{
	t_env	*new_node;
	char	*ptr_to_equal_sign;

	ptr_to_equal_sign = ft_strchr(envp, '=');
	if (!ptr_to_equal_sign)
		return (NULL);
	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		print_error_and_exit("malloc failure");
	new_node->id = ft_substr(envp, 0, ptr_to_equal_sign - envp);
	if (!new_node->id)
		print_error_and_exit("substr failure");
	new_node->str = x_strdup(ptr_to_equal_sign + 1);
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}
