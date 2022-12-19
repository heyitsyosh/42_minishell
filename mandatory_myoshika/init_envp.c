/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 21:59:16 by myoshika          #+#    #+#             */
/*   Updated: 2022/12/18 01:59:20 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//need to error handle <ltoa> malloc error
static void	set_shlvl(t_env *shlvl, t_minishell *m)
{
	int64_t	original_shlvl;
	char	*check;

	if (!shlvl || !shlvl->str)
		return ;
	original_shlvl = ft_strtol(shlvl->str, &check, 10);
	if (*check || errno == ERANGE)
		return ;
	original_shlvl++;
	free(shlvl->str);
	shlvl->str = ft_ltoa(original_shlvl);
	if (!shlvl->str)
		free_all_and_exit(m);
}

static t_env	*make_envp_list(char **envp, t_minishell *m)
{
	size_t	i;
	t_env	*new_node;
	t_env	*envp_head;
	t_env	*envp_tail;

	i = 0;
	while (envp[i])
	{
		new_node = make_node(envp[i]);
		if (!new_node || !new_node->id || !new_node->str)
			free_all_and_exit(m);
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

void	init_envp(char **envp, t_minishell *m)
{
	m->envp_head = make_envp_list(envp, m);
	set_shlvl(get_env("SHLVL", m->envp_head), m);
	//set oldpwd if nonexistent?
	//set pwd if nonexistent?
}
