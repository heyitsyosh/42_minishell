/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 02:43:22 by myoshika          #+#    #+#             */
/*   Updated: 2023/08/31 23:03:15 by myoshika         ###   ########.fr       */
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

static int	run_left_of_pipe(t_ast *ast, int input_fd)
{
	int			fd[2];
	int			saved_io[2];
	t_ast		*left_of_pipe;

	save_io(saved_io);
	if (ast->left->type != PIPE_NODE || run_left_of_pipe(ast->left, input_fd))
	{
		if (pipe(fd) == -1)
			print_error_and_exit("pipe failure");
		x_dup2(input_fd, STDIN_FILENO);
		x_dup2(fd[1], STDOUT_FILENO);
		x_dup2(fd[0], input_fd);
		x_close(fd[0]);
		x_close(fd[1]);
		if (ast->left->type != PIPE_NODE)
			left_of_pipe = ast->left;
		else
			left_of_pipe = (ast->left)->right;
		left_of_pipe->pipe_status = BESIDE_PIPE;
		left_of_pipe->input_fd = input_fd;
		execute(left_of_pipe);
	}
	restore_io(saved_io);
	return (input_fd);
}

static int	run_right_of_pipe(t_ast *ast, int input_fd)
{
	int			fd[2];
	int			saved_io[2];

	save_io(saved_io);
	x_dup2(input_fd, STDIN_FILENO);
	ast->right->pipe_status = BESIDE_PIPE;
	ast->right->input_fd = input_fd;
	execute(ast->right);
	restore_io(saved_io);
}

int	execute_pipeline(t_ast *ast)
{
	int	stdin_dup;
	int	input_fd;

	stdin_dup = x_dup(STDIN_FILENO);
	input_fd = run_left_of_pipe(ast, stdin_dup);
	run_right_of_pipe(ast, input_fd);
	close(stdin_dup);
}
