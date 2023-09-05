/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 02:43:22 by myoshika          #+#    #+#             */
/*   Updated: 2023/09/06 04:55:47 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <unistd.h> //close, STDIN_FILENO

static void	execute_pipeline_elem(t_pipeline *pipeline, t_data *d)
{
	if (pipeline->pipe_elem->type == SUBSHELL_NODE)
		execute_subshell(pipeline->pipe_elem, d);
	else if (pipeline->pipe_elem->type == CMD_NODE)
		execute_cmd(pipeline->pipe_elem, d);
}

static int	run_pipes(int input_fd, t_pipeline *pipeline, t_data *d)
{
	int			fd[2];
	int			saved_io[2];

	save_io(saved_io);
	set_pipe(input_fd, fd);
	pipeline->pipe_elem->input_fd = input_fd;
	execute_pipeline_elem(pipeline, d);
	restore_io(saved_io);
	return (input_fd);
}

static int	run_last_pipe(int input_fd, t_pipeline *pipeline, t_data *d)
{
	int			fd[2];
	int			saved_io[2];

	save_io(saved_io);
	x_dup2(input_fd, STDIN_FILENO);
	pipeline->pipe_elem->input_fd = input_fd;
	execute_pipeline_elem(pipeline, d);
	restore_io(saved_io);
}

static bool	is_last_pipeline(t_pipeline *pipeline)
{
	return (pipeline->next == NULL);
}

void	execute_pipeline(t_ast *ast, t_data *d)
{
	int			stdin_dup;
	int			input_fd;
	t_pipeline	*pipeline;
	t_pipeline	*pipeline_head;

	pipeline = NULL;
	flatten_ast(ast, &pipeline);
	pipeline_head = pipeline;
	stdin_dup = x_dup(STDIN_FILENO);
	input_fd = stdin_dup;
	while (!is_last_pipeline(pipeline))
	{
		input_fd = run_pipes(input_fd, pipeline, d);
		pipeline = pipeline->next;
	}
	run_last_pipe(input_fd, pipeline, d);
	close(stdin_dup);
	wait_all_children(pipeline, d);
	free_pipeline_list(pipeline_head);
}
