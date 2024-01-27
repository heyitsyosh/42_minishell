/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 00:37:37 by myoshika          #+#    #+#             */
/*   Updated: 2023/09/06 22:37:34 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h> //malloc, free

void	free_pipeline_list(t_pipeline *pipeline)
{
	t_pipeline	*pipeline_to_free;

	while (pipeline)
	{
		pipeline_to_free = pipeline;
		pipeline = pipeline->next;
		free(pipeline_to_free);
	}
}

static t_pipeline	*make_pipeline_node(t_ast *pipe_elem)
{
	t_pipeline	*new;

	new = (t_pipeline *)malloc(sizeof(t_pipeline));
	if (!new)
		print_error_and_exit("malloc failure");
	pipe_elem->pipe_status = BESIDE_PIPE;
	new->pipe_elem = pipe_elem;
	new->next = NULL;
	return (new);
}

static void	add_pipe_elem(t_ast *pipe_elem, t_pipeline **pipeline)
{
	t_pipeline	*new;

	new = make_pipeline_node(pipe_elem);
	if (!*pipeline)
		*pipeline = new;
	else
	{
		new->next = *pipeline;
		*pipeline = new;
	}
}

void	flatten_ast(t_ast *pipe_elem, t_pipeline **pipeline)
{
	if (pipe_elem->type == PIPE_NODE)
	{
		add_pipe_elem(pipe_elem->right, pipeline);
		flatten_ast(pipe_elem->left, pipeline);
	}
	else
		add_pipe_elem(pipe_elem, pipeline);
}
