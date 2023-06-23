/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_to_list_ii.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 22:27:04 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/23 11:25:23 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"
#include "../../includes/minishell.h"
#include "../../includes/expand.h"
#include "../../includes/libft.h"

char	*get_quoted_str(char *quote, size_t *i)
{
	size_t		quoted_len;
	char		*quoted;

	quoted_len = 0;
	while (quote[*i] && quote[*i] != '\'')
	{
		quoted_len++;
		(*i)++;
	}
	quoted = ft_substr(quote, 1, quoted_len);
	if (!quoted)
		print_error_and_exit("substr failure");
	return (quoted);
}

char	*get_dquoted_str(char *dquote, size_t *i)
{
	size_t	index_mover;
	char	*new_portion;
	char	*dquoted;

	dquoted = xstrdup("");
	while (dquote[*i] && dquote[*i] != '\"')
	{
		index_mover = 0;
		if (dquote[*i] == '\\' && ft_strchr("\\\'\"$", dquote[*i + 1]))
		{
			index_mover = 2;
			new_portion = ft_substr(dquote + *i, 1, 1);
		}
		else if (dquote[*i] == '$')
			new_portion = variable_expansion(dquote + *i + 1, &index_mover);
		else
		{
			index_mover = no_interpretation_len(dquote + *i, IN_DQUOTE);
			new_portion = ft_substr(dquote + *i, 0, index_mover);
		}
		*i += index_mover;
		dquoted = ft_strjoin_with_free(dquoted, new_portion, FREE_BOTH);
	}
	return (dquoted);
}

char	*get_unquoted_str(char *no_quote, size_t *i)
{
	size_t	index_mover;
	char	*new_portion;
	char	*unquoted;

	unquoted = xstrdup("");
	while (no_quote[*i] && !ft_strchr("\'\"*", no_quote[*i]))
	{
		index_mover = 0;
		if (no_quote[*i] == '\\' && ft_strchr("\\\'\"$", no_quote[*i + 1]))
		{
			index_mover = 2;
			new_portion = ft_substr(no_quote + *i, 1, 1);
		}
		else if (no_quote[*i] == '$')
			new_portion = variable_expansion(no_quote + *i + 1, &index_mover);
		else
		{
			index_mover = no_interpretation_len(no_quote + *i, NOT_IN_DQUOTE);
			new_portion = ft_substr(no_quote + *i, 0, index_mover);
		}
		*i += index_mover;
		unquoted = ft_strjoin_with_free(unquoted, new_portion, FREE_BOTH);
	}
	return (unquoted);
}
