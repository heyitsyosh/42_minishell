/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshono <cshono@student.42.tokyo>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 01:33:26 by cshono            #+#    #+#             */
/*   Updated: 2022/12/25 18:31:56 by cshono           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	builtin_unset(char *line, t_minishell *m)
{
	t_env	*env;
	t_env	*ret_env;
	t_env	*prev_env;
	t_env	*next_env;

	env = m->envp_head;
	if (!env)
		return;
	ret_env = get_env(line, env);
	prev_env = ret_env->prev;
	next_env = ret_env->next;
	prev_env->next = next_env;
}
