/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 07:57:49 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/19 01:44:50 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include <stdlib.h> //malloc, free

bool	is_unexpected(t_token_type type, t_token_type next_type)
{
	if (type == PIPE || type == AND || type == OR || \
		type == OPEN_PARENTHESIS || type == UNSET)
	{
		if (next_type == PIPE || next_type == AND || \
			next_type == OR || type == CLOSE_PARENTHESIS)
			return (true);
	}
	return (false);
}

t_ast	*set_syntax_error(t_token *tok, t_parse *p)
{
	if (!tok)
		p->syntax_err_location = ft_strdup("newline");
	else
		p->syntax_err_location = ft_strdup(tok->word);
	if (!p->syntax_err_location)
		print_error_and_exit("strdup failure");
	return (NULL);
}

t_ast	*make_ast_node(t_ast_node_type type, t_ast *lhs, t_ast *rhs)
{
	t_ast	*root;

	root = (t_ast *)malloc(sizeof(t_ast));
	if (!root)
		print_error_and_exit("malloc failure");
	root->cmd = NULL;
	root->type = type;
	root->left = lhs;
	root->right = rhs;
	return (root);
}

t_parse	*init_p(void)
{
	t_parse	*p;

	p = (t_parse *)malloc(sizeof(t_parse));
	if (!p)
		print_error_and_exit("malloc failure");
	p->tmp_args = NULL;
	p->syntax_err_location = NULL;
	return (p);
}

void	free_p(t_parse **p)
{
	if (*p)
	{
		free((*p)->syntax_err_location);
		free(*p);
	}
}
