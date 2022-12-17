/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 04:35:25 by myoshika          #+#    #+#             */
/*   Updated: 2022/12/18 02:01:56 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	get_type(char *cursor)
{
	if (*cursor == '|')
		return (PIPE);
	else if (*cursor == '>')
		return (GREATER);
	else if (*cursor == '<')
		return (LESSER);
	else if (*cursor == '(')
		return (LEFT_PARENTHESIS);
	else if (*cursor == ')')
		return (RIGHT_PARENTHESIS);
	else if (*cursor == '&')
		return (AND);
	return (GENERAL);
}

// static char	*extract_quoted_str()
// {
	
// }

// static char	*extract_non_operator_token(char *cursor, t_token *t)
// {
// 	size_t		i;
// 	char		*token;

// 	i = 0;
// 	while (cursor[i] && !ft_strchr("|<>()", cursor[i]))
// 	{
// 		if (cursor[i] == '\'' && ft_strchr(&cursor[i + 1], '\''))
			
// 		if (cursor[i] == '\"' && ft_strchr(&cursor[i + 1], '\"'))
			
// 		i++;
// 	}
// 	return (token);
// }

static char	*extract_operator_token_ii(char *cursor, t_token *t)
{
	if (t->type == GREATER && cursor[1] == '>')
	{
		t->type = APPEND;
		return (ft_strdup(">>"));
	}
	else if (t->type == GREATER)
		return (ft_strdup(">"));
	else if (t->type == LESSER && cursor[1] == '<')
	{
		t->type = HEREDOC;
		return (ft_strdup("<<"));
	}
	else if (t->type == LESSER)
		return (ft_strdup("<"));
	else
		return (extract_non_operator_token(cursor, t));
}

static char	*extract_operator_token(char *cursor, t_token *t)
{
	if (t->type == AND && cursor[1] == '&')
	{
		t->type = AND;
		return (ft_strdup("&&"));
	}
	else if (t->type == AND)
		t->type = GENERAL;
	else if (t->type == PIPE && cursor[1] == '|')
	{
		t->type = OR;
		return (ft_strdup("||"));
	}
	else if (t->type == PIPE)
		return (ft_strdup("|"));
	else if (t->type == LEFT_PARENTHESIS)
		return (ft_strdup("("));
	else if (t->type == RIGHT_PARENTHESIS)
		return (ft_strdup(")"));
	else
		return (extract_operator_token_ii(cursor, t));
}

static size_t	fill_token_info(t_token *t, char *cursor)
{
	size_t	token_len;

	token_len = 0;
	ft_bzero(t, sizeof(t_token));
	t->type = get_type(t->token);
	t->token = extract_token(cursor, t);
	if (t->token)
		token_len = ft_strlen(t->token);
	return (token_len);
}

void	tokenize(char *line, t_minishell *m)
{
	size_t	i;
	t_token	*new_token;

	i = 0;
	while (line[i])
	{
		while (ft_isspace(line[i]))
			i++;
		if (!line[i])
			break ;
		new_token = malloc(sizeof(t_token));
		if (!new_token)
			free_all_and_exit(m);
		i += fill_token_info(new_token, line[i]);
		if (!new_token->token)
			free_all_and_exit(m);
	}
}

	// <
	// <<
	// >>
	// >
	// |
	// ||
	// &&
	// ()
	// ""
	// ''
	
	/*
	${PWD} $(PWD) $[PWD]
	< (echo "a" || cat "b")
	*/