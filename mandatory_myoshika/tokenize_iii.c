/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_iii.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 21:59:16 by myoshika          #+#    #+#             */
/*   Updated: 2022/12/21 21:13:14 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*extract_quoted_str(&cursor)
{
	
}

char	*extract_general_str(&cursor)
{
	
}

static char	*join_sub_tokens(t_list	*sub_tokens)
{
	char	*joined;

	joined = ft_strdup("");
	while (sub_tokens)
	{
		joined = ft_strjoin_with_free(joined, (char *)sub_tokens->content, 1);
		free(sub_tokens->content);
		sub_tokens = sub_tokens->next;
	}
	return (joined);
}

char	*extract_general_token(char *cursor, size_t *ignored_len, t_token *t)
{
	char	*sub_token;
	char	*joined;

	while (!ft_isspace(*cursor) && t->type <= DQUOTE)
	{
		if (t->type == QUOTE)
			sub_token = extract_quoted_str(&cursor);
		if (t->type == DQUOTE)
			sub_token = extract_quoted_str(&cursor);
		else
			sub_token = extract_general_str(&cursor);
		joined = ft_strjoin_with_free(joined, sub_token, FREE_FIRST_PARAM);
		free(sub_token);
		t->type = get_type(cursor);
	}
	t->type = GENERAL;
	return (joined);
}