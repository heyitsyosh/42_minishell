/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 04:49:33 by myoshika          #+#    #+#             */
/*   Updated: 2023/09/07 21:51:10 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"
#include "../../includes/ft_printf.h"
#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include <stdlib.h> //free
#include <unistd.h> //STDERR_FILENO

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
	while (is_redir(*tok) && !*syntax_err)
		parse_redir(tok, node, syntax_err);
	return (node);
}

t_ast	*parse_pipe(t_token **tok, char **syntax_err)
{
	t_ast	*node;
	t_ast	*right_child;

	node = parse_cmd(tok, syntax_err);
	while (tok_is(PIPE, *tok) && !*syntax_err)
	{
		if (is_unexpected((*tok)->next))
		{
			if (node)
				free_ast(node);
			return (set_syntax_error((*tok)->next, syntax_err));
		}
		*tok = (*tok)->next;
		right_child = parse_cmd(tok, syntax_err);
		node = make_ast_node(PIPE_NODE, node, right_child);
	}
	return (node);
}

t_ast	*create_ast(t_token **tok, char	**syntax_err)
{
	t_ast			*node;
	t_ast			*right_child;
	t_ast_node_type	type;

	node = parse_pipe(tok, syntax_err);
	while ((tok_is(AND, *tok) || tok_is(OR, *tok)) && !*syntax_err)
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
		right_child = parse_pipe(tok, syntax_err);
		node = make_ast_node(type, node, right_child);
	}
	return (node);
}

t_ast	*parser(t_token *tok)
{
	t_ast	*ast;
	char	*syntax_err;

	ast = NULL;
	syntax_err = NULL;
	if (!tok)
		return (NULL);
	if (is_unexpected(tok))
		set_syntax_error(tok, &syntax_err);
	else
		ast = create_ast(&tok, &syntax_err);
	if (!syntax_err && tok)
		set_syntax_error(tok, &syntax_err);
	if (syntax_err)
	{
		ft_dprintf(STDERR_FILENO, \
			"syntax error near unexpected token `%s'\n", syntax_err);
		free(syntax_err);
		free_ast(ast);
		return (NULL);
	}
	return (ast);
}
