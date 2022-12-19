/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 22:31:32 by myoshika          #+#    #+#             */
/*   Updated: 2022/12/19 18:49:04 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_exit(t_minishell *m)
{
	if (m->line)
		free(m->line);
	if (m->old_pwd)
		free(m->old_pwd);
	if (m->pwd)
		free(m->pwd);
	if (m->envp_head)
		free_envs(m->envp_head);
	if (m->token_head)
		free_tokens(m->token_head);
	//exitの挙動をそろえる
}
