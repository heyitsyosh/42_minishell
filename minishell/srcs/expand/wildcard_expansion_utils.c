/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expansion_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 01:36:43 by myoshika          #+#    #+#             */
/*   Updated: 2024/04/12 04:18:24 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static char	*find_matching_substr( \
		char *d_name, char *sub_word, bool active_wildcard)
{
	char	*ptr_to_matching_substr;

	if (active_wildcard)
		ptr_to_matching_substr = ft_strstr(d_name, sub_word);
	else
	{
		if (ft_strncmp(d_name, sub_word, ft_strlen(sub_word)))
			ptr_to_matching_substr = NULL;
		else
			ptr_to_matching_substr = d_name;
	}
	return (ptr_to_matching_substr);
}

static bool	check_last_substr(char *d_name, t_word *word)
{
	size_t	sub_word_len;
	size_t	d_name_len;

	if (word->type == WILDCARD)
		return (true);
	if (!*d_name)
		return (false);
	sub_word_len = ft_strlen(word->sub_word);
	d_name_len = ft_strlen(d_name);
	while (sub_word_len-- && d_name_len--)
	{
		if (d_name[d_name_len] != word->sub_word[sub_word_len])
			return (false);
	}
	return (true);
}

bool	matches_pattern(char *d_name, t_word *word)
{
	bool	active_wildcard;
	char	*ptr_to_matching_substr;

	active_wildcard = false;
	while (word->next)
	{
		if (word->type == WILDCARD)
			active_wildcard = true;
		else
		{
			ptr_to_matching_substr = \
				find_matching_substr(d_name, word->sub_word, active_wildcard);
			if (!ptr_to_matching_substr)
				return (false);
			d_name = ptr_to_matching_substr + ft_strlen(word->sub_word);
			active_wildcard = false;
		}
		word = word->next;
	}
	return (check_last_substr(d_name, word));
}
