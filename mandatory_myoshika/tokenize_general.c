/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_iii.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 21:59:16 by myoshika          #+#    #+#             */
/*   Updated: 2022/12/28 15:01:14 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*extract_general_str(char **cursor)
{
	size_t	i;
	char	*general_str;

	i = 0;
	while (get_token_type(*cursor) == GENERAL)
		i++;
	general_str = ft_substr(*cursor, 0, i);
	*cursor += i;
	return (general_str);
}

char	*extract_general_token(char **cursor, t_type type)
{
	char	*token;

	if (type == QUOTE)
		token = extract_quoted_str(cursor, '\'');
	else if (type == DQUOTE)
		token = extract_quoted_str(cursor, '\"');
	else
		token = extract_general_str(cursor);
	return (token);
}
