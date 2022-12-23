/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_iii.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 21:59:16 by myoshika          #+#    #+#             */
/*   Updated: 2022/12/23 09:30:53 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// size_t	count_quoted_str_len(char **cursor, char quote_type)
// {
	
// }

// static char	*extract_quoted_str(char **cursor, char quote_type)
// {
// 	size_t	len;
// 	char	*quoted_str;
// 	bool	has_closing_quote;

// 	has_closing_quote = false;
// 	len = count_quoted_str_len(*cursor, &has_closing_quote);
// 	if (!has_closing_quote)
// 	{
// 		*cursor++;
// 		return ()
// 	}
// 	quoted_str = malloc(len);
// 	while (len)
// 	{
		
// 	}
// 	*cursor += i;
// 	return (quoted_str);
// }

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

	while (!ft_isspace(**cursor) && type <= DQUOTE)
	{
		if (type == QUOTE)
			sub_token = extract_quoted_str(cursor, '\'');
		if (type == DQUOTE)
			sub_token = extract_quoted_str(cursor, '"');
		else
			sub_token = extract_general_str(cursor);
		joined = ft_strjoin_with_free(joined, sub_token, FREE_FIRST_PARAM);
		free(sub_token);
		type = get_type(*cursor);
	}
	return (joined);
}
