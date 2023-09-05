/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 02:43:22 by myoshika          #+#    #+#             */
/*   Updated: 2023/09/05 22:01:24 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <unistd.h> //close, STDIN_FILENO

static void	execute_pipeline_elem(t_ast *ast, t_pids **pid_list, t_data *d)
{
	if (ast->type == SUBSHELL_NODE)
		execute_subshell(ast, pid_list, d);
	else if (ast->type == CMD_NODE)
		execute_cmd(ast, pid_list, d);
}

static int	run_left_of_pipe( \
	t_ast *left_node, int input_fd, t_pids **pid_list, t_data *d)
{
	int			fd[2];
	int			saved_io[2];

	save_io(saved_io);
	if (left_node->type == PIPE)
		run_left_of_pipe(left_node->left, input_fd, pid_list, d);
	set_pipe(input_fd, fd);
	if (left_node->type == PIPE)
		left_node = left_node->right;
	left_node->pipe_status = BESIDE_PIPE;
	left_node->input_fd = input_fd;
	execute_pipeline_elem(left_node, pid_list, d);
	restore_io(saved_io);
	return (input_fd);
}

static int	run_right_of_pipe( \
	t_ast *right_node, int input_fd, t_pids **pid_list, t_data *d)
{
	int			fd[2];
	int			saved_io[2];

	save_io(saved_io);
	x_dup2(input_fd, STDIN_FILENO);
	right_node->pipe_status = LAST_PIPE;
	right_node->input_fd = input_fd;
	execute_pipeline_elem(right_node, pid_list, d);
	restore_io(saved_io);
}

void	execute_pipeline(t_ast *ast, t_data *d)
{
	int		stdin_dup;
	int		input_fd;
	t_pids	*pid_list;

	pid_list = NULL;
	stdin_dup = x_dup(STDIN_FILENO);
	input_fd = run_left_of_pipe(ast->left, stdin_dup, &pid_list, d);
	run_right_of_pipe(ast->right, input_fd, &pid_list, d);
	close(stdin_dup);
	wait_all_children(pid_list->next, d);
	free_pid_list(pid_list);
}
