/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 04:32:24 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/11 22:18:42 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft.h"
#include "../includes/get_next_line.h"

char	*quote(char **quote_ptr)
{
	size_t		quoted_len;
	char		*quoted;
	const char	*quote = *quote_ptr;

	quoted_len = 1;
	while (quote[quoted_len] && quote[quoted_len] != '\'')
		quoted_len++;
	quoted = ft_substr(quote, 0, quoted_len);
	if (!quoted)
		print_error_and_exit("substr failure");
	return (no_interpretation_if_not_closed(quoted, quote_ptr, quoted_len));
}

char	*dquote(char **dquote_ptr, char *dquoted, size_t i)
{
	size_t		index_mover;
	char		*new_portion;
	const char	*dquote = *dquote_ptr;

	dquoted = ft_strdup("\"");
	while (dquote[i] && dquote[i] != '\"')
	{
		index_mover = 0;
		if (dquote[i] == '\\' && ft_strchr("\\\'\"$", dquote[i + 1]))
		{
			index_mover = 2;
			new_portion = ft_substr(dquote[i], 1, 1);
		}
		else if (dquote[i] == '$')
			new_portion = variable_expansion(dquote[i + 1], &index_mover);
		else
		{
			index_mover = no_interpretation_len(dquote[i], IN_DQUOTE);
			new_portion = ft_substr(dquote[i], 0, index_mover);
		}
		i += index_mover;
		dquoted = ft_strjoin_with_free(dquoted, new_portion, FREE_BOTH);
	}
	return (no_interpretation_if_not_closed(dquoted, dquote_ptr, i));
}

//might do word splitting and emulate parameters in heredoc