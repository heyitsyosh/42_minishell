/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_token_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 21:59:16 by myoshika          #+#    #+#             */
/*   Updated: 2022/12/19 17:10:41 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*extract_quoted_str(char *cursor, char quote_type)
{
	return (ft_substr(cursor[i], 0, cursor + i - ));
}

static char	*extract_non_operator_token(char *cursor, t_token *t)
{
	size_t		i;
	char		*token;

	i = 0;
	while (!ft_strchr("|<>()", cursor[i]) && !ft_isspace(cursor[i]))
	{
		if (cursor[i] == '\'' && ft_strchr(&cursor[i + 1], '\''))
			extract_quoted_str(cursor[i + 1], '\'');
		else if (cursor[i] == '\"' && ft_strchr(&cursor[i + 1], '\"'))
			extract_quoted_str(cursor[i + 1], '\"');
		else
			
		i++;
	}
	return (token);
}

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

char	*extract_operator_token(char *cursor, t_token *t)
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
