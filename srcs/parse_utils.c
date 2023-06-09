/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 17:51:44 by myoshika          #+#    #+#             */
/*   Updated: 2023/05/27 05:27:40 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft.h"
#include "../includes/get_next_line.h"

t_ast_node	*make_ast_node(t_ast_node_type type)
{
	t_ast_node	*new_node;

	new_node = (t_ast_node *)malloc(sizeof(t_ast_node));
	if (!new_node)
		print_error_and_exit("malloc failure");
	new_node->type = type;
	new_node->left_child = NULL;
	new_node->right_child = NULL;
	return (new_node);
}

t_parse	*init_parse_struct(t_token *tok)
{
	t_parse	*p;

	p = (t_parse *)malloc(sizeof(t_parse));
	if (!p)
		print_error_and_exit("malloc failure");
	p->current_tok = tok;
	p->cmd_list_head = NULL;
	return (p);
}

void	attatch_ast_nodes(t_ast_node *base, t_ast_node *left, t_ast_node *right)
{
	base->left = left;
	base->right = right;
}

bool	tok_type_is(t_token_type type, t_parse *p)
{
	if (p->current_tok_type == type)
		return (true);
	return (false);
}

void	move_tok_forward(t_parse *p)
{
	p->current_tok = p->current_tok->next;
}
