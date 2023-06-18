/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:35:57 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/19 01:46:31 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libft.h"

bool	is_redir(t_token *tok)
{
	return (tok->type == WORD || tok->type == IO_NUMBER \
	|| tok->type == REDIRECT_APPEND || tok->type == HEREDOC \
	|| tok->type == REDIRECT_IN || tok->type == REDIRECT_OUT);
}

// void	add_redir(t_token **tok, t_ast *cmd_node)
// {
	
// }

//add current token to list of command and its args
//list is temporarily saved in (p->tmp_args),
//then is later converted to a (char **) to be used in execve
static void	add_cmd_element(t_token **tok, t_parse *p)
{
	char	*to_add;
	t_token	*tmp_args;

	to_add = ft_strdup((*tok)->word);
	if (!to_add)
		print_error_and_exit("strdup failure");
	if (!p->tmp_args)
		p->tmp_args = make_token(to_add, UNSET);
	else
	{
		tmp_args = p->tmp_args;
		while (tmp_args->next)
			tmp_args = tmp_args->next;
		tmp_args->next = make_token(to_add, UNSET);
	}
	*tok = (*tok)->next;
}

t_ast	*parse_cmd(t_token **tok, t_parse *p)
{
	t_ast	*node;

	node = parse_subshell(tok, p);
	if (node)
		return (node);
	if (!(*tok) || ((*tok)->type != WORD && !is_redir(*tok)))
		return (NULL);
	node = make_ast_node(UNSET, NULL, NULL);
	while (*tok && ((*tok)->type == WORD || is_redir(*tok)))
	{
		if ((*tok)->type == WORD)
			add_cmd_element(tok, p);
		// if (is_redir((*tok)->type))
		// 	add_redir(node, p);
	}
	arg_list_to_dbl_ptr(node, p);
	return (node);
}
