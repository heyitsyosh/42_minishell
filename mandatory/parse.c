/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 04:49:33 by myoshika          #+#    #+#             */
/*   Updated: 2023/05/25 19:09:34 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft.h"
#include "../includes/get_next_line.h"

/*
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
*/

t_ast_node	*parse_subshell(t_parse *p)
{
	t_ast_node	*subshell_node;

	if (p->current_tok->type != OPEN_PARENTHESIS)
		return (NULL);
	p->current_tok = p->current_tok->next;
	return (node);
}

t_ast_node	*parse_cmd(t_parse *p)
{
	if (parse_subshell())
		return (NULL);
}

t_ast_node	*parse_and_or(t_parse *p)
{
		if (parse_cmd())
		return (NULL);
}

t_ast_node	*parse_pipe(t_parse *p)
{
	if (parse_and_or())
		return (NULL);
}

//"<<", ">>", "<", ">", "|", "(", ")", "&&", "||"
t_ast_node	*parser(t_token *tok)
{
	t_parse			*p;
	t_ast_node		*syntax_tree;

	p = init_parse_struct(tok);
	syntax_tree = parse_pipe(p);
	//check for error
	//then return root of tree
	// return ();
}
