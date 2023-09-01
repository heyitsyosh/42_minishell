/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 02:43:22 by myoshika          #+#    #+#             */
/*   Updated: 2023/09/02 00:20:20 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <unistd.h> //pipe

static void	save_io(int saved_io[2])
{
	saved_io[0] = x_dup(STDIN_FILENO);
	saved_io[1] = x_dup(STDOUT_FILENO);
}

static void	restore_io(int saved_io[2])
{
	x_dup2(saved_io[0], STDIN_FILENO);
	x_dup2(saved_io[1], STDOUT_FILENO);
	x_close(saved_io[0]);
	x_close(saved_io[1]);
}

static bool	node_is_operator(t_ast *ast)
{
	if (ast->type == PIPE_NODE \
		|| ast->type == AND_NODE \
		|| ast->type == OR_NODE)
		return (true);
	return (false);
}

int	run_right_of_pipe(t_ast *right_of_pipe, int input_fd)
{
	int			fd[2];
	int			saved_io[2];

	save_io(saved_io);
	x_dup2(input_fd, STDIN_FILENO);
	right_of_pipe->pipe_status = BESIDE_PIPE;
	right_of_pipe->input_fd = input_fd;
	execute(right_of_pipe);
	restore_io(saved_io);
}

int	run_left_of_pipe(t_ast *left_of_pipe, int input_fd)
{
	int			fd[2];
	int			saved_io[2];

	save_io(saved_io);
	if (left_of_pipe->left && left_of_pipe->left->type == PIPE_NODE)
		run_left_of_pipe(left_of_pipe->left, input_fd);
	else
	{
		if (pipe(fd) == -1)
			print_error_and_exit("pipe failure");
		x_dup2(input_fd, STDIN_FILENO);
		x_dup2(fd[1], STDOUT_FILENO);
		x_dup2(fd[0], input_fd);
		x_close(fd[0]);
		x_close(fd[1]);
		left_of_pipe->pipe_status = BESIDE_PIPE;
		left_of_pipe->input_fd = input_fd;
		execute(left_of_pipe);
	}
	restore_io(saved_io);
	return (input_fd);
}
