/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 04:49:33 by myoshika          #+#    #+#             */
/*   Updated: 2023/05/30 18:25:08 by myoshika         ###   ########.fr       */
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

bool	parse_subshell(t_parse *p)
{
	t_ast_node	*subshell;
	t_ast_node	*compound_list;

	if (p->current_tok->type != OPEN_PARENTHESIS)
		return (NULL);
	p->current_tok = p->current_tok->next;
	compound_list = parse_and_or(p);
	if (p->current_tok->type == NIL)
	{
		// 	UNEXPECTED EOF 
	}
	subshell = make_ast_node(SUBSHELL_NODE);
	attatch_ast_nodes(subshell, compound_list, NULL);
	return (true);
}

bool	parse_simple_command(t_parse *p)
{
	t_ast_node	*cmd_node;
}

bool	parse_cmd(t_parse *p)
{
	t_ast_node	*cmd_node;
	t_ast_node	*subtree;

	subtree = parse_subshell(p);
	if (subtree)
		return (subtree);
	cmd_node = parse_simple_command(p);
	if (cmd_node)
		return (cmd_node);
	//return (NULL);
	//check for error from parse_subshell and parse_simple_command
}

bool	parse_pipe(t_parse *p)
{
	t_ast_node	*cmd_node;
	t_ast_node	*subtree;

	subtree = parse_subshell(p);
	if (subtree)
		return (subtree);
	cmd_node = parse_simple_command(p);
	if (cmd_node)
		return (cmd_node);
	//return (NULL);
	//check for error from parse_subshell and parse_simple_command
}

void	add_cmd(t_parse *p)
{
	t_ast_node	*and_or_node;
	t_ast_node	*subtree;
}

bool	parse_and_or(t_parse *p)
{
	t_commands	*command;
	t

	while (!tok_type_is(NIL, p))
	{
		if (tok_type_is(AND, p) || tok_type_is(OR, p))
		{
			move_tok_forward(p);
			parse_pipe(p);
			
		}
		else
			break ;
	}
}

//"<<", ">>", "<", ">", "|", "(", ")", "&&", "||"
t_parse	*parser(t_token *tok)
{
	t_parse			*p;

	p = init_parse_struct(tok);
	parse_and_or(p);
	//check for error
	return (p);
}
