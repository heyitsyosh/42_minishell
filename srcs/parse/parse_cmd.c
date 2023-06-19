/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:35:57 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/20 02:07:42 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libft.h"

static t_cmd	*make_cmd_struct(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		print_error_and_exit("malloc failure");
	cmd->command = NULL;
	cmd->args = NULL;
	cmd->arg_list = NULL;
	return (cmd);
}

static void	add_cmd_element(t_token **tok, t_ast *node)
{
	char	*to_add;
	t_token	*tmp;

	node->type = CMD_NODE;
	to_add = ft_strdup((*tok)->word);
	if (!to_add)
		print_error_and_exit("strdup failure");
	if (!node->cmd->arg_list)
		node->cmd->arg_list = make_token(to_add, WORD);
	else
	{
		tmp = node->cmd->arg_list;
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
	if (!tok_is(WORD, *tok) || !is_redir(*tok))
		return (NULL);
	node = make_ast_node(UNSET, NULL, NULL);
	node->cmd = make_cmd_struct();
	while ((tok_is(WORD, *tok) || is_redir(*tok)) && !syntax_err)
	{
		if (tok_is(WORD, *tok))
			add_cmd_element(tok, node);
		else if (is_redir(*tok))
			parse_redirection(tok, node, syntax_err);
	}
	if (syntax_err)
	{
		free_ast(node);
		return (NULL);
	}
	return (node);
}
