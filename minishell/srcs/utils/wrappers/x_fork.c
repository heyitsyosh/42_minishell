/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_fork.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 19:44:11 by myoshika          #+#    #+#             */
/*   Updated: 2024/04/12 04:16:19 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "minishell.h"
#include <unistd.h> //fork
#include <errno.h> //errno

pid_t	x_fork(t_data *d)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		if (errno == EAGAIN)
		{
			d->exit_status = 1;
			d->fork_failed = 1;
			ft_dprintf(STDERR_FILENO, \
				"fork: Resource temporarily unavailable\n");
		}
		else
			print_error_and_exit("fork failure");
	}
	return (pid);
}
