/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:35:57 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/17 02:33:45 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft.h"

bool	is_redir(t_token *tok)
{
	return (tok->type == WORD || tok->type == IO_NUMBER \
	|| tok->type == REDIR_APPEND || tok->type == HEREDOC \
	|| tok->type == REDIR_IN || tok->type == REDIR_OUT);
}

// void	add_redir(t_token **tok, t_ast *cmd_node)
// {
	
// }

//add current token to list of command and its args
//list is temporarily saved in (p->tmp_args),
//then is later converted to a (char **) to be used in execve
void	add_cmd_element(t_token **tok, t_parse *p)
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
	if (!(*tok) || ((*tok)->type != WORD))
		return (NULL);
	node = make_ast_node(CMD_NODE, NULL, NULL);
	while (*tok && ((*tok)->type == WORD || is_redir(*tok)))
	{
		if ((*tok)->type == WORD)
			add_cmd_element(tok, p);
		if (is_redir((*tok)->type))
			add_redir(node, p); ////////////////
	}
	arg_list_to_dbl_ptr(node, p);
	else
	{
		free_ast(node);
		node = NULL;
	}
	return (node);
}
