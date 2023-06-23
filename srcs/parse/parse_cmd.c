/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:35:57 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/23 15:38:46 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libft.h"

static void	add_cmd_element(t_token **tok, t_ast *node)
{
	char	*to_add;
	t_token	*tmp;

	to_add = x_strdup((*tok)->word);
	if (!node->cmd_list)
		node->cmd_list = make_token(to_add, WORD);
	else
	{
		tmp = node->cmd_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = make_token(to_add, WORD);
	}
	*tok = (*tok)->next;
}

t_ast	*parse_cmd(t_token **tok, char **syntax_err)
{
	t_ast	*node;

	node = parse_subshell(tok, syntax_err);
	if (node)
		return (node);
	if (!tok_is(WORD, *tok) && !is_redir(*tok))
		return (NULL);
	node = make_ast_node(CMD_NODE, NULL, NULL);
	while ((tok_is(WORD, *tok) || is_redir(*tok)) && !*syntax_err)
	{
		if (tok_is(WORD, *tok))
			add_cmd_element(tok, node);
		else
			parse_redir(tok, node, syntax_err);
	}
	if (*syntax_err)
	{
		free_ast(node);
		return (NULL);
	}
	return (node);
}
