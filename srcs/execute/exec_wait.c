/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_wait.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:18:37 by myoshika          #+#    #+#             */
/*   Updated: 2023/09/05 19:03:10 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"
#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include <sys/types.h> // W*
#include <sys/wait.h> //wait, waitpid
#include <unistd.h> //STDERR_FILENO
#include <errno.h> //errno

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

void	wait_for_last_child(pid_t last_pid, t_data *d)
{
	int		wait_status;
	pid_t	wait_result;

	while (1)
	{
		wait_result = wait(&wait_status);
		if (wait_result == last_pid)
			set_exit_status(wait_status, d);
		else if (wait_result < 0)
		{
			if (errno == ECHILD)
				break ;
			else
				print_error_and_exit("wait failure");
		}
	}
}

void	wait_for_no_pipe(t_ast *ast_node, pid_t pid, t_data *d)
{
	int	wait_status;

	if (ast_node->pipe_status == NO_PIPE)
	{
		if (waitpid(pid, &wait_status, 0) == -1)
			print_error_and_exit("waitpid failure");
		set_exit_status(wait_status, d);
	}
}
