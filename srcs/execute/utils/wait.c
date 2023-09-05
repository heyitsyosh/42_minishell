/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 20:39:08 by myoshika          #+#    #+#             */
/*   Updated: 2023/09/05 22:49:16 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_printf.h"
#include "../../../includes/minishell.h"
#include "../../../includes/libft.h"
#include <sys/types.h> // W*
#include <sys/wait.h> //waitpid
#include <unistd.h> //STDERR_FILENO

static void	set_exit_status(int wait_status, t_data *d)
{
	if (WIFEXITED(wait_status))
		d->exit_status = WEXITSTATUS(wait_status);
	else if (WIFSIGNALED(wait_status))
	{
		d->exit_status = WTERMSIG(wait_status) + 128;
		if (WTERMSIG(wait_status) == SIGINT)
			ft_dprintf(STDERR_FILENO, "\n");
	}
}

void	wait_one_child(pid_t pid, t_data *d)
{
	int	wait_status;

	if (waitpid(pid, &wait_status, 0) == -1)
		print_error_and_exit("waitpid failure");
	set_exit_status(wait_status, d);
}

void	wait_all_children(t_pids *pids, t_data *d)
{
	int		wait_status;
	pid_t	wait_result;

	while (pids)
	{
		if (waitpid(pids->pid, &wait_status, 0) == -1)
			print_error_and_exit("waitpid failure");
		pids = pids->next;
	}
	set_exit_status(wait_status, d);
}
