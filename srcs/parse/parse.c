/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 04:49:33 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/20 18:38:55 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"
#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include <stdlib.h> //free

t_ast	*parse_subshell(t_token **tok, char **syntax_err)
{
	t_ast	*node;
	t_ast	*left_child;

	if (!tok_is(OPEN_PARENTHESIS, *tok))
		return (NULL);
	if (is_unexpected((*tok)->next))
		return (set_syntax_error((*tok)->next, syntax_err));
	node = make_ast_node(SUBSHELL_NODE, NULL, NULL);
	*tok = (*tok)->next;
	left_child = create_ast(tok, syntax_err);
	node->left = left_child;
	if (!tok_is(CLOSE_PARENTHESIS, *tok))
	{
		free_ast(node);
		return (set_syntax_error(*tok, syntax_err));
	}
	else
		*tok = (*tok)->next;
	while (is_redir(*tok))
		parse_redirect(node, tok);
	return (node);
}

t_ast	*parse_and_or(t_token **tok, char **syntax_err)
{
	t_ast			*node;
	t_ast			*right_child;
	t_ast_node_type	type;

	node = parse_cmd(tok, syntax_err);
	while ((tok_is(AND, *tok) || tok_is(OR, *tok)))
	{
		if ((*tok)->type == AND)
			type = AND_NODE;
		else
			type = OR_NODE;
		if (is_unexpected((*tok)->next))
		{
			if (node)
				free_ast(node);
			return (set_syntax_error((*tok)->next, syntax_err));
		}
		*tok = (*tok)->next;
		right_child = parse_cmd(tok, syntax_err);
		node = make_ast_node(type, node, right_child);
	}
	return (node);
}

t_ast	*create_ast(t_token **tok, char	**syntax_err)
{
	t_ast	*node;
	t_ast	*right_child;

	node = parse_and_or(tok, syntax_err);
	while (tok_is(PIPE, *tok))
	{
		if (is_unexpected((*tok)->next))
		{
			if (node)
				free_ast(node);
			return (set_syntax_error((*tok)->next, syntax_err));
		}
		*tok = (*tok)->next;
		right_child = parse_and_or(tok, syntax_err);
		node = make_ast_node(PIPE_NODE, node, right_child);
	}
	return (node);
}

t_ast	*parser(t_token *tok)
{
	t_ast	*ast;
	char	*syntax_err;

	syntax_err = NULL;
	if (!tok || is_unexpected(tok))
		set_syntax_error(tok, &syntax_err);
	else
		ast = create_ast(&tok, &syntax_err);
	if (syntax_err)
	{
		msg_to_stderr("syntax error near unexpected token `", syntax_err, "'\n");
		free(syntax_err);
		free_ast(ast);
		return (NULL);
	}
	return (ast);
}
