/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_pipe_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 20:45:41 by myoshika          #+#    #+#             */
/*   Updated: 2023/09/05 21:50:47 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include <unistd.h> //pipe, STIN_FILENO, STDOUT_FILENO

void	save_io(int saved_io[2])
{
	saved_io[0] = x_dup(STDIN_FILENO);
	saved_io[1] = x_dup(STDOUT_FILENO);
}

void	restore_io(int saved_io[2])
{
	x_dup2(saved_io[0], STDIN_FILENO);
	x_dup2(saved_io[1], STDOUT_FILENO);
	x_close(saved_io[0]);
	x_close(saved_io[1]);
}

void	set_pipe(int input_fd, int fd[2])
{
	if (pipe(fd) == -1)
		print_error_and_exit("pipe failure");
	x_dup2(input_fd, STDIN_FILENO);
	x_dup2(fd[1], STDOUT_FILENO);
	x_dup2(fd[0], input_fd);
	x_close(fd[0]);
	x_close(fd[1]);
}
