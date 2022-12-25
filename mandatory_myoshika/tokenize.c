/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 04:35:25 by myoshika          #+#    #+#             */
/*   Updated: 2022/12/21 21:12:33 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_type(char *cursor)
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
	else if (*cursor == '&' && *(cursor + 1) == '&')
		return (AND);
	else if (*cursor == '\'')
		return (QUOTE);
	else if (*cursor == '"')
		return (DQUOTE);
	return (GENERAL);
}

static size_t	fill_token_info(t_token *t, char *cursor)
{
	size_t	ignored_len;

	ignored_len = 0;
	t->type = get_type(t->token);
	if (t->type == GENERAL || t->type == QUOTE || t->type == DQUOTE)
		t->token = extract_general_token(cursor, &ignored_len);
	else
		t->token = extract_operator_token(cursor, t);
	if (!t->token)
		exit(EXIT_FAILURE);
	t->next = NULL;
	t->prev = NULL;
	return (ft_strlen(t->token) + ignored_len);
}

static	void	token_add_back(t_env *token, t_env *token_to_add)
{
	if (token == token_to_add)
		return ;
	while (token->next)
		token = token->next;
	token->next = token_to_add;
	token_to_add->prev = token;
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
			exit(EXIT_SUCCESS);
		i += fill_token_info(new_token, line[i]);
		if (!new_token->token)
			exit(EXIT_SUCCESS);
		if (!m->token_head)
			m->token_head = new_token;
		token_add_back(m->token_head, new_token);
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