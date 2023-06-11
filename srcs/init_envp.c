/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 21:59:16 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/11 19:45:44 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h> //free
#include <unistd.h> //getcwd
#include <errno.h> //errno, ERANGE

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

//in the case of "env -i ./minishell", minishell is run without envp
//set_pwd anticipates that scenario and prevents error
static void	set_pwd(t_env *pwd)
{
	char	*current_dir;

	current_dir = getcwd(NULL, 0);
	if (!current_dir)
		print_error_and_exit("getcwd failure");
	if (!pwd)
	{
		pwd = make_env_node("PWD=");
		free(pwd->str);
		pwd->str = current_dir;
	}
	g_ms.pwd = current_dir;
}

static void	set_shlvl(t_env *shlvl)
{
	long	original_shlvl;
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
		print_error_and_exit("ltoa failure");
}

void	init_envp(char **envp)
{
	g_ms.envp_head = make_envp_list(envp);
	set_pwd(get_env("PWD", g_ms.envp_head));
	set_shlvl(get_env("SHLVL", g_ms.envp_head));
}
