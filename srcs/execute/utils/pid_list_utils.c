/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 21:23:32 by myoshika          #+#    #+#             */
/*   Updated: 2023/09/05 21:54:15 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include <stdlib.h> //malloc, free

void	free_pid_list(t_pids *pid_list)
{
	t_pids	*tmp;

	while (pid_list)
	{
		tmp = pid_list->next;
		free(pid_list);
		pid_list = tmp;
	}
}

static t_pids	*make_pid_node(pid_t pid, int pipe_status)
{
	t_pids	*new;

	new = (t_pids *)malloc(sizeof(t_pids));
	if (!new)
		print_error_and_exit("malloc failure");
	new->pid = pid;
	new->is_last_pipe = false;
	if (pipe_status == LAST_PIPE)
		new->is_last_pipe = true;
	new->next = NULL;
	return (new);
}

void	add_pid(pid_t pid, t_pids **pid_list, int pipe_status)
{
	t_pids	*new;

	new = make_pid_node(pid, pipe_status);
	if (!*pid_list)
		*pid_list = new;
	else
	{
		new->next = *pid_list;
		*pid_list = new;
	}
}
