/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 04:49:33 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/19 18:31:40 by myoshika         ###   ########.fr       */
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

	if ((*tok)->type != OPEN_PARENTHESIS)
		return (NULL);
	if (is_unexpected((*tok)->next))
		return (set_syntax_error((*tok)->next, syntax_err));
	node = make_ast_node(SUBSHELL_NODE, NULL, NULL);
	*tok = (*tok)->next;
	left_child = create_ast(tok, syntax_err);
	node->left = left_child;
	if (!(*tok) || (*tok)->type != CLOSE_PARENTHESIS)
	{
		free_ast(node);
		return (set_syntax_error(*tok, syntax_err));
	}
	else
		*tok = (*tok)->next;
	while (is_redir(*tok))
		parse_redirection(node, tok);
	return (node);
}

t_ast	*parse_and_or(t_token **tok, char **syntax_err)
{
	t_ast			*node;
	t_ast			*right_child;
	t_ast_node_type	type;

	node = parse_cmd(tok, syntax_err);
	while (*tok && ((*tok)->type == AND || (*tok)->type == OR))
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
	while (*tok && (*tok)->type == PIPE)
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
