/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 21:59:16 by myoshika          #+#    #+#             */
/*   Updated: 2022/12/12 18:13:41 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>

static bool	str_is_num(char *str)
{
	if (!str)
		return (false);
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if ('0' > *str || *str > '9')
			return (false);
		str++;
	}
	return (true);
}

//kuriagari is Japanese for carrying a digit over during addition
static void	set_shlvl(t_env *shlvl)
{
	size_t	shlvl_len;
	bool	kuriagari;

	if (!shlvl || !str_is_num(shlvl->str))
		return ;
	shlvl_len = ft_strlen(shlvl->str);
	kuriagari = true;
	while (shlvl_len-- && kuriagari)
	{
		shlvl->str[shlvl_len] += 1;
		if (shlvl->str[shlvl_len] == '9' + 1)
			shlvl->str[shlvl_len] = '0';
		else
			kuriagari = false;
	}
	if (kuriagari)
		shlvl->str = ft_strjoin_with_free("1", shlvl->str, FREE_SECOND_PARAM);
	//error handle <shlvl->str> malloc error
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
	new_node->var = ft_substr(envp, 0, ptr_to_equal_sign - envp);
	new_node->str = ft_strdup(ptr_to_equal_sign + 1);
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

bool	node_add_back(t_env *envp, t_env *new_node)
{
	if (envp == new_node)
		return (false);
	while (envp->next)
		envp = envp->next;
	envp->next = new_node;
	new_node->prev = envp;
}

static t_env	*make_envp_list(char	**envp)
{
	int		i;
	t_env	*new_node;
	t_env	*envp_head;
	t_env	*envp_tail;

	i = 0;
	while (envp[i])
	{
		new_node = make_node(envp[i]);
		//error handle <new_node> malloc error
		if (i == 0)
		{
			envp_head = new_node;
			envp_tail = new_node;
		}
		node_add_back(envp_tail, new_node);
		envp_tail = new_node;
		i++;
	}
	return (envp_head);
}

void	init_shell(t_minishell *m, char **envp)
{
	m->envp_head = make_envp_list(envp);
	set_shlvl(get_env("SHLVL", m->envp_head));
	//set oldpwd if nonexistent?
	//set pwd if nonexistent?
}
