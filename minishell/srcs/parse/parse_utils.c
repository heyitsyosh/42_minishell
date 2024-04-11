/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 07:57:49 by myoshika          #+#    #+#             */
/*   Updated: 2024/04/12 04:17:53 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h> //malloc

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
		*syntax_err = x_strdup("newline");
	else
		*syntax_err = x_strdup(tok->word);
	return (NULL);
}

t_ast	*make_ast_node(t_ast_node_type type, t_ast *lhs, t_ast *rhs)
{
	t_ast	*new;

	new = (t_ast *)malloc(sizeof(t_ast));
	if (!new)
		print_error_and_exit("malloc failure");
	new->cmd_list = NULL;
	new->redir = NULL;
	new->type = type;
	new->pipe_status = NO_PIPE;
	new->input_fd = -1;
	new->pid = 0;
	new->left = lhs;
	new->right = rhs;
	return (new);
}

bool	tok_is(t_token_type type, t_token *tok)
{
	if (!tok)
		return (false);
	return (tok->type == type);
}
