/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:35:57 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/19 02:58:37 by myoshika         ###   ########.fr       */
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

// void	add_redir(t_token **tok, t_ast *cmd_node)
// {
	
// }

//add current token to list of command and its args
//list is temporarily saved in (p->tmp_args),
//then is later converted to a (char **) to be used in execve
static void	add_cmd_element(t_token **tok, t_cmd *cmd)
{
	char	*to_add;
	t_token	*tmp;

	to_add = ft_strdup((*tok)->word);
	if (!to_add)
		print_error_and_exit("strdup failure");
	if (!cmd->arg_list)
		cmd->arg_list = make_token(to_add, WORD);
	else
	{
		tmp = cmd->arg_list;
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
	if (!(*tok) || ((*tok)->type != WORD && !is_redir(*tok)))
		return (NULL);
	node = make_ast_node(UNSET, NULL, NULL);
	node->cmd = make_cmd_struct();
	while (*tok && ((*tok)->type == WORD || is_redir(*tok)))
	{
		if ((*tok)->type == WORD)
			add_cmd_element(tok, node->cmd);
		// if (is_redir((*tok)->type))
		// 	add_redir(node, p);
	}
	//when node is still unset at this point??
	return (node);
}
