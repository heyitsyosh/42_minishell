/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 21:59:16 by myoshika          #+#    #+#             */
/*   Updated: 2022/12/12 00:51:57 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>

static void	set_shlvl(t_env *envp)
{
	int	old_lvl;

	while (envp)
	{
		if (!strcmp(envp->var, "SHLVL"))
		{
			ft_strtol();
			
			break ;
		}
		envp = envp->next
	}
}

static t_env	*make_node(char	*envp)
{
	t_env	*new_node;
	char	*ptr_to_equal_sign;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	ptr_to_equal_sign = ft_strchr(envp, '=');
	new_node->var = ft_substr(envp, 0, ptr_to_equal_sign - envp);
	new_node->string = ft_strdup(ptr_to_equal_sign + 1);
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

static void	node_add_back(t_env **envp_tail, t_env *new_node)
{
	if (*envp_tail == new_node)
		return ;
	(*envp_tail)->next = new_node;
	new_node->prev = *envp_tail;
	*envp_tail = new_node;
}

static t_env	*make_envp_list(char	**envp)
{
	int		i;
	t_env	*envp_head;
	t_env	*envp_tail;
	t_env	*new_node;

	i = 0;
	while (envp[i])
	{
		new_node = make_node(envp[i]);
		// if (!new_node)
		// 	return ();
		if (i == 0)
		{
			envp_head = new_node;
			envp_tail = new_node;
		}
		node_add_back(&envp_tail, new_node);
		i++;
	}
	return (envp_head);
}

void	init_shell(t_minishell *m, char **envp)
{
	m->envp_head = make_envp_list(envp);
	while (m->envp_head)
	{
		printf("%s=%s\n", m->envp_head->var, m->envp_head->string);
		m->envp_head = m->envp_head->next;
	}
	set_shlvl(m->envp_head);
}
