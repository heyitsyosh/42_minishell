/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 22:54:08 by myoshika          #+#    #+#             */
/*   Updated: 2023/05/30 17:11:34 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	delete_env(t_env *to_delete)
{
	t_env	*next_env;
	t_env	*prev_env;

	next_env = to_delete->next;
	prev_env = to_delete->prev;
	if (prev_env)
		prev_env->next = next_env;
	if (next_env)
		next_env->prev = prev_env;
	free(to_delete);
}

int	builtin_unset(t_toke *args, t_minishell *m)
{
	t_env	*matching_id;

	matching_id = (get_env(id, m->envp_head));
	if (matching_id)
	{
		if (matching_id == m->envp_head)
			m->envp_head = matching_id->next;
		delete_env(matching_id);
	}
}
