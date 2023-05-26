/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 17:51:44 by myoshika          #+#    #+#             */
/*   Updated: 2023/05/25 18:09:24 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft.h"
#include "../includes/get_next_line.h"

t_ast_node	*make_ast_node(t_token *token)
{
	t_ast_node	*new_node;

	new_node = (t_ast_node *)malloc(sizeof(t_ast_node));
	if (!new_node)
		print_error_and_exit("malloc failure");
	new_node->token = token;
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
	return (p);
}
