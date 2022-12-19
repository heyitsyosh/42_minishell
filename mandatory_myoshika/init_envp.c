/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 21:59:16 by myoshika          #+#    #+#             */
/*   Updated: 2022/12/19 19:28:51 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		exit(EXIT_SUCCESS);
}

static t_env	*make_envp_list(char **envp, t_minishell *m)
{
	size_t	i;
	t_env	*new_env;
	t_env	*envp_head;
	t_env	*envp_tail;

	i = 0;
	while (envp[i])
	{
		new_env = make_env_node(envp[i]);
		if (!new_env || !new_env->id || !new_env->str)
			exit(EXIT_FAILURE);
		if (i == 0)
		{
			envp_head = new_env;
			envp_tail = new_env;
		}
		env_add_back(envp_tail, new_env);
		envp_tail = new_env;
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
