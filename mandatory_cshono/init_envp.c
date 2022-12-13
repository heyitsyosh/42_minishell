/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshono <cshono@student.42.tokyo>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 21:59:16 by myoshika          #+#    #+#             */
/*   Updated: 2022/12/12 22:46:24 by cshono           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>



// void	ft_lstdelone(t_env *lst, void (*del)(void *))
// {
// 	if (!(lst == NULL || del == NULL))
// 		del(lst->str);
// 	free(lst);
// }

// void	ft_lstclear(t_env **lst, void (*del)(void *))
// {
// 	t_list	*tmp;

// 	if (lst == NULL)
// 		return ;
// 	while (*lst != NULL)
// 	{
// 		tmp = (*lst)->next;
// 		ft_lstdelone(*lst, del);
// 		*lst = tmp;
// 	}
// }

static t_env	*get_env(char *str, t_env *env)
{
	// while (env->next != '\0')
	// {
	// 	if (env->string == str)
	// }
	while (str != env->str)
	{
		env = env->next;
	}
	if (env == NULL)
		return (NULL);
	return (env);
}

// static void	set_shlvl(t_env *envp)
// {
// 	int	old_lvl;

// 	while (envp)
// 	{
// 		if (!strcmp(envp->var, "SHLVL"))
// 		{
// 			ft_strtol();
			
// 			break ;
// 		}
// 		envp = envp->next
// 	}
// }

static t_env	*make_node(char	*envp)
{
	t_env	*new_node;
	char	*ptr_to_equal_sign;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	ptr_to_equal_sign = ft_strchr(envp, '=');
	new_node->var = ft_substr(envp, 0, ptr_to_equal_sign - envp);
	new_node->str = ft_strdup(ptr_to_equal_sign + 1);
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
	t_env *kakunin;
	t_env *syutsuryoku;
	t_env *head;
	

	m->envp_head = make_envp_list(envp);
	head = m->envp_head;
	kakunin = m->envp_head;
	while (m->envp_head)
	{
		printf("%s=%s\n", m->envp_head->var, m->envp_head->str);
		m->envp_head = m->envp_head->next;
	}
	//kakunin = m->envp_head;
	syutsuryoku = get_env("PWD", kakunin);
	printf("get_envは; %s\n", syutsuryoku->str);
	//ft_lstclear(head,del);
	// set_shlvl(m->envp_head);
}
