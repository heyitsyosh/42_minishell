/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 04:49:33 by myoshika          #+#    #+#             */
/*   Updated: 2023/04/19 21:18:40 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft.h"
#include "../includes/get_next_line.h"

t_token	*tokdup(t_token *tok)
{
	char	*word_dup;

	word_dup = ft_strdup(tok->word);
	if (!word_dup)
		print_error_and_exit("strdup failure");
	return (make_token(word_dup, tok->type));
}

t_token	*arg_last(t_token *args)
{
	if (!args)
		return (NULL);
	while (args->next)
		args = args->next;
	return (args);
}

void	append_token(t_token **args, t_token *tok_to_add)
{
	t_token	*last_arg;

	if (!*args)
		*args = tok_to_add;
	else
	{
		last_arg = arg_last(*args);
		last_arg->next = tok_to_add;
	}
}

t_ast_node	*make_ast_node(t_token *token)
{
	t_ast_node	*new_node;

	new_node = (t_ast_node *)malloc(sizeof(t_ast_node));
	if (!new_node)
		print_error_and_exit("malloc failure");
	new_node->token = token;
	new_node->left_child = NULL;
	new_node->right_child = NULL;
	return (new_node);
}

//"<<", ">>", "<", ">", "|", "(", ")", "&&", "||"
t_ast_node	*parser(t_token **tok)
{
	t_ast_node		*syntax_tree;

	syntax_tree = command();

	return ();
}



t_ast_node	*command()
{
	t_ast_node	*node;
	while (tok->type != NIL)
	{
		
		if (tok->type == WORD)
			;
		else if (tok->type == REDIR_OUT || tok->type == REDIR_IN \
			|| tok->type == HEREDOC || tok->type == REDIR_APPEND)
			
		else if (tok->type == IO_NUMBER)
			
		else
			break;
	}
	return (node);
}
