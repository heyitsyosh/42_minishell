/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_token_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 21:59:16 by myoshika          #+#    #+#             */
/*   Updated: 2022/12/19 19:31:02 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static size_t	attatch_unquoted_str(char **token, char *cursor)
{
	size_t	len;
	char	*str;

	len = 0;
	while (!ft_strchr("|<>()'\"", cursor[len]) && )
		len++;
	str = ft_substr(cursor, 0, len);
	if (token)
		*token = ft_strjoin_with_free(*token, str, FREE_FIRST_PARAM);
	free(str);
	return (len);
}

static size_t	attatch_quoted_str(char **token, char *cursor, char quote_type, t_token *t)
{
	size_t	len;
	char	*quoted_str;

	len = cursor - ft_strchr(cursor, quote_type);
	// if (*(cursor + len - 1) == ft_strchr(cursor, quote_type)
	quoted_str = ft_substr(cursor, 0, len);
	if (token)
		*token = ft_strjoin_with_free(*token, quoted_str, FREE_FIRST_PARAM);
	free(quoted_str);
	t->total_quotes++;
	return (len + 2);
}

//strchr to find the closing quote/dquote doesn't make sense with backslash
static char	*extract_non_operator_token(char *cursor, t_token *t)
{
	char		*token;

	token = ft_strdup("");
	while (!ft_strchr("|<>()", *cursor) && !ft_isspace(*cursor))
	{
		if (*cursor == '\'' && ft_strchr(cursor + 1, '\''))
			cursor += attatch_quoted_str(&token, cursor + 1, '\'', t);
		else if (*cursor == '\"' && ft_strchr(cursor + 1, '\"'))
			cursor += attatch_quoted_str(&token, cursor + 1, '\"', t);
		else
			cursor += attatch_unquoted_str(&token, cursor);
		cursor++;
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
