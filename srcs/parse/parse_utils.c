/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 07:57:49 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/23 09:37:30 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include <stdlib.h> //malloc, free

bool	is_redir(t_token *tok)
{
	if (!tok)
		return (false);
	return (tok->type == IO_NUMBER \
	|| tok->type == RD_APPEND || tok->type == RD_IN \
	|| tok->type == RD_HEREDOC || tok->type == RD_OUT);
}

bool	is_unexpected(t_token *next)
{
	if (!next)
		return (true);
	if (next->type == PIPE || next->type == AND || \
		next->type == OR || next->type == CLOSE_PARENTHESIS)
		return (true);
	return (false);
}

t_ast	*set_syntax_error(t_token *tok, char **syntax_err)
{
	if (!tok)
		*syntax_err = ft_strdup("newline");
	else
		*syntax_err = ft_strdup(tok->word);
	if (!*syntax_err)
		print_error_and_exit("strdup failure");
	g_ms.exit_status = 2;
	return (NULL);
}

t_ast	*make_ast_node(t_ast_node_type type, t_ast *lhs, t_ast *rhs)
{
	t_ast	*root;

	root = (t_ast *)malloc(sizeof(t_ast));
	if (!root)
		print_error_and_exit("malloc failure");
	root->cmd_list = NULL;
	root->redir = NULL;
	root->type = type;
	root->left = lhs;
	root->right = rhs;
	return (root);
}

bool	tok_is(t_token_type type, t_token *tok)
{
	if (!tok)
		return (false);
	return (tok->type == type);
}
