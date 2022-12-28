/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_quoted.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:01:24 by myoshika          #+#    #+#             */
/*   Updated: 2022/12/28 17:10:59 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	quoted_str_len(char *cursor, char quote_type)
{
	size_t	len;

	len = 0;
	while (*cursor && *cursor != quote_type)
	{
		if (quote_type == '\"' && *cursor == '\\'
			&& ft_strchr("$\\\"", *(cursor + 1)))
		len++;
		cursor++;
	}
	return (len);
}

char	*extract(char **cursor, char quote_type, size_t len)
{
	char	*quoted_str;

	quoted_str = malloc(len + 1);
	if (!quoted_str)
		exit(EXIT_FAILURE);
	while (len--)
	{
		if (cursor[0][0] == '\\' && quote_type == '\"'
			&& ft_strchr("\"", cursor[0][1]))
			(*cursor)++;
		*quoted_str++ = **cursor;
		(*cursor)++;
	}
	*quoted_str = '\0';
	return (quoted_str);
}

static char	*extract_quoted_str(char **cursor, char quote_type)
{
	size_t	len;
	char	*quoted_str;
	bool	has_closing_quote;

	has_closing_quote = ;
	len = quoted_str_len(*cursor, quote_type, &has_closing_quote);
	if (has_closing_quote)
		quoted_str = extract(cursor, quote_type, (len + 2));
	else
		
	return (quoted_str);
}
