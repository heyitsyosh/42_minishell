/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:55:58 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/21 21:52:09 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h> //malloc, free

t_redir	*make_redir_struct(void)
{
	t_redir	*redir;

	redir = (t_redir *)malloc(sizeof(t_redir));
	if (!redir)
		print_error_and_exit("malloc failure");
	redir->filename = NULL;
	redir->delimitor = NULL;
	redir->prev = NULL;
	redir->next = NULL;
	return (redir);
}

static t_redir	*get_last_redir(t_redir *redir)
{
	while (redir->next)
		redir = redir->next;
	return (redir);
}

void	add_redir_to_list(t_ast *node, t_redir *redir_to_add)
{
	t_redir	*last_redir;

	if (!node->redir)
	{
		node->redir = redir_to_add;
		return ;
	}
	last_redir = get_last_redir(node->redir);
	last_redir->next = redir_to_add;
	redir_to_add->prev = last_redir;
}
