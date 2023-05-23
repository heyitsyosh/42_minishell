/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 21:59:16 by myoshika          #+#    #+#             */
/*   Updated: 2023/05/23 23:37:07 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_env	*make_envp_list(char **envp)
{
	size_t	i;
	t_env	*new_env;
	t_env	*envp_head;
	t_env	*envp_tail;

	i = 0;
	while (envp[i])
	{
		new_env = make_env_node(envp[i]);
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

//in the case of "env -e ./minishell", minishell is run without envp
//set_pwd anticipates that scenario and prevents error
static void	set_pwd(t_env *pwd, t_minishell *m)
{
	char	*current_dir;

	current_dir = getcwd(NULL, 0);
	if (!current_dir)
		exit(EXIT_FAILURE);
	if (!pwd)
	{
		pwd = make_env_node("PWD=");
		free(pwd->str);
		pwd->str = current_dir;
	}
	m->pwd = current_dir;
	if (!m->pwd)
		exit(EXIT_FAILURE);
}

static void	set_shlvl(t_env *shlvl)
{
	int64_t	original_shlvl;
	char	*check;

	if (!shlvl)
		shlvl = make_env_node("SHLVL=0");
	original_shlvl = ft_strtol(shlvl->str, &check, 10);
	if (*check || errno == ERANGE)
		return ;
	original_shlvl++;
	free(shlvl->str);
	shlvl->str = ft_ltoa(original_shlvl);
	if (!shlvl->str)
		exit(EXIT_SUCCESS);
}

void	init_envp(char **envp, t_minishell *m)
{
	m->envp_head = make_envp_list(envp);
	set_pwd(get_env("PWD", m->envp_head), m);
	set_shlvl(get_env("SHLVL", m->envp_head));
}
