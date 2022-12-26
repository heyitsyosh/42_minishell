/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_iii.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 21:59:16 by myoshika          #+#    #+#             */
/*   Updated: 2022/12/26 15:57:01 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	quoted_str_len(char *cursor, char quote_type, bool *has_closing_quote)
{
	size_t	len;

	len = 0;
	if (*cursor == quote_type)
	{
		cursor++;
		len++;
	}
	while (*cursor && *cursor != quote_type)
	{
		if (quote_type == '\"' && *cursor == '\\'
			&& ft_strchr("$\\\"", *(cursor + 1)))
		len++;
		cursor++;
	}
	if (*cursor == quote_type)
	{
		if (has_closing_quote)
			*has_closing_quote = true;
		len++;
	}
	return (len);
}

void	extract(char **cursor, char *quoted_str, char quote_type)
{
	

	while (**cursor)
	{
		if (cursor[0][0] == '\\' && quote_type == '\"'
			&& ft_strchr("\"", cursor[0][1]))
			(*cursor)++;
		*quoted_str++ = **cursor;
		(*cursor)++;
	}
}

static char	*extract_quoted_str(char **cursor, char quote_type)
{
	size_t	len;
	char	*quoted_str;
	bool	has_closing_quote;

	has_closing_quote = false;
	len = quoted_str_len(*cursor, quote_type, &has_closing_quote);
	if (has_closing_quote)
	{
		quoted_str = malloc(len + 1);
		if (!quoted_str)
			exit(EXIT_FAILURE);
		extract(cursor, quoted_str, len);
	}
	else
	{
		(*cursor)++;
		if (quote_type == '\'')
			return (ft_strdup("\'"));
		return (ft_strdup("\""));
	}
	return (quoted_str);
}

char	*extract_general_str(char **cursor)
{
	size_t	i;
	char	*general_str;

	i = 0;
	while (!isspace((*cursor)[i]) && get_type((*cursor)[i]) == GENERAL)
		i++;
	general_str = ft_substr(*cursor, 0, i);
	*cursor += i;
	return (general_str);
}

char	*extract_general_token(char **cursor, t_type type)
{
	char	*sub_token;
	char	*joined;

	joined = ft_strdup("");
	while (**cursor && !ft_isspace(**cursor) && type <= DQUOTE)
	{
		if (type == QUOTE)
			sub_token = extract_quoted_str(cursor, '\'');
		else if (type == DQUOTE)
			sub_token = extract_quoted_str(cursor, '\"');
		else
			sub_token = extract_general_str(cursor);
		joined = ft_strjoin_with_free(joined, sub_token, FREE_FIRST_PARAM);
		free(sub_token);
		type = get_type(*cursor);
	}
	return (joined);
}
