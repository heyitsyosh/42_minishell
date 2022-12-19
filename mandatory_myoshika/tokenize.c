/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 04:35:25 by myoshika          #+#    #+#             */
/*   Updated: 2022/12/19 16:47:19 by myoshika         ###   ########.fr       */
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