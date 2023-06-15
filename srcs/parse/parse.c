/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 04:49:33 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/15 18:51:37 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"
#include "../includes/minishell.h"
#include "../includes/libft.h"

t_ast	*parse_subshell(t_token **tok, t_parse *p)
{
	t_ast	*node;
	t_ast	*right_child;

	if ((*tok)->type != OPEN_PARENTHESIS)
		return (NULL);
		
	return (node);
}

t_ast	*parse_and_or(t_token **tok, t_parse *p)
{
	t_ast			*node;
	t_ast			*right_child;
	t_ast_node_type	type;

	node = parse_cmd(tok, p);
	while (*tok && ((*tok)->type == AND || (*tok)->type == OR))
	{
		if ((*tok)->type == AND)
			type = AND_NODE;
		else
			type = OR_NODE;
		if (!(*tok)->next || is_unexpected((*tok)->type, (*tok)->next->type))
			return (set_syntax_error((*tok)->next, p));
		*tok = (*tok)->next;
		right_child = parse_cmd(tok, p);
		node = make_ast_node(type, node, right_child);
	}
	return (node);
}

t_ast	*create_ast(t_token **tok, t_parse *p)
{
	t_ast	*node;
	t_ast	*right_child;

	node = parse_and_or(tok, p);
	while (*tok && (*tok)->type == PIPE)
	{
		if (!(*tok)->next || is_unexpected((*tok)->type, (*tok)->next->type))
			return (set_syntax_error((*tok)->next, p));
		*tok = (*tok)->next;
		right_child = parse_and_or(tok, p);
		node = make_ast_node(PIPE_NODE, node, right_child);
	}
	return (node);
}

t_parse	*parser(t_token *tok)
{
	t_ast	*ast;
	t_parse	*p;

	p = init_p(&p);
	ast = create_ast(&tok);
	if (p->syntax_err_location)
	{
		msg_to_stderr("syntax error near unexpected token `", \
			p->syntax_err_location, "'");
		free_parse_struct(&p);
		free_ast(ast);
		return (NULL);
	}
	free_parse_struct(&p);
	return (ast);
}
