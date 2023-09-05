/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 02:43:22 by myoshika          #+#    #+#             */
/*   Updated: 2023/09/05 18:36:44 by myoshika         ###   ########.fr       */
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

static void	set_pipe(int input_fd, int fd[2])
{
	if (pipe(fd) == -1)
		print_error_and_exit("pipe failure");
	x_dup2(input_fd, STDIN_FILENO);
	x_dup2(fd[1], STDOUT_FILENO);
	x_dup2(fd[0], input_fd);
	x_close(fd[0]);
	x_close(fd[1]);
}

int	run_left_of_pipe(t_ast *ast, int input_fd, t_data *d)
{
	int			fd[2];
	int			saved_io[2];
	t_ast		*left_of_pipe;

	save_io(saved_io);
	if ((ast->left)->type == PIPE)
		run_left_of_pipe(ast->left, input_fd, d);
	set_pipe(input_fd, fd);
	if ((ast->left)->type != PIPE)
		left_of_pipe = ast->left;
	else
		left_of_pipe = (ast->left)->right;
	left_of_pipe->pipe_status = BESIDE_PIPE;
	left_of_pipe->input_fd = input_fd;
	execute(left_of_pipe, d);
	restore_io(saved_io);
	return (input_fd);
}

pid_t	run_right_of_pipe(t_ast *right_of_pipe, int input_fd, t_data *d)
{
	pid_t		pid;
	int			fd[2];
	int			saved_io[2];

	save_io(saved_io);
	x_dup2(input_fd, STDIN_FILENO);
	right_of_pipe->pipe_status = BESIDE_PIPE;
	right_of_pipe->input_fd = input_fd;
	if (right_of_pipe->type == CMD_NODE)
		pid = execute_cmd(right_of_pipe, d);
	else
		pid = execute_subshell(right_of_pipe, d);
	restore_io(saved_io);
	return (pid);
}
