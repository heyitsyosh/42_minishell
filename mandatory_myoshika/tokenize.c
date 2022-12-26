/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 04:35:25 by myoshika          #+#    #+#             */
/*   Updated: 2022/12/26 21:20:12 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_token_type(char *cursor)
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
	else if (*cursor == '\0')
		return (NIL);
	return (GENERAL);
}

static void	fill_token_info(t_token *t, char **line)
{
	t->type = get_token_type(*line);
	if (t->type == GENERAL || t->type == QUOTE || t->type == DQUOTE)
	{
		t->token = extract_general_token(line, t->type);
		t->type = GENERAL;
	}
	else
	{
		t->token = extract_operator_token(*line, t);
		if (t->token)
			*line += ft_strlen(t->token);
	}
	printf("type:%d\n", t->type);
	fflush(stdout);
	printf("t->token:%s\n", t->token);
	fflush(stdout);
	if (!t->token)
		exit(EXIT_FAILURE);
	t->next = NULL;
	t->prev = NULL;
}

static	void	token_add_back(t_token *token, t_token *token_to_add)
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
	t_token	*new_token;

	while (*line)
	{
		while (ft_isspace(*line))
			line++;
		if (!*line)
			break ;
		new_token = malloc(sizeof(t_token));
		if (!new_token)
			exit(EXIT_SUCCESS);
		fill_token_info(new_token, &line);
		if (!m->token_head)
			m->token_head = new_token;
		token_add_back(m->token_head, new_token);
	}
}
