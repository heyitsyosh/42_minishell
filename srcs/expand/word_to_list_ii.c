/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_to_list_ii.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 22:27:04 by myoshika          #+#    #+#             */
/*   Updated: 2023/09/09 22:53:52 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"
#include "../../includes/minishell.h"
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

char	*get_dquoted_str(char *dquote, size_t *i, t_data *d)
{
	size_t	i_mover;
	char	*new_portion;
	char	*dquoted;

	dquoted = x_strdup("");
	while (dquote[*i] && dquote[*i] != '\"')
	{
		i_mover = 0;
		if (dquote[*i] == '\\' && ft_strchr("\\\'\"$", dquote[*i + 1]))
		{
			i_mover = 2;
			new_portion = ft_substr(dquote + *i, 1, 1);
		}
		else if (dquote[*i] == '$')
			new_portion = variable_expansion(dquote + *i + 1, &i_mover, d);
		else
		{
			i_mover = no_interpretation_len(dquote + *i, IN_DQUOTE);
			new_portion = ft_substr(dquote + *i, 0, i_mover);
		}
		*i += i_mover;
		dquoted = x_strjoin_free(dquoted, new_portion, FREE_BOTH);
	}
	return (dquoted);
}

char	*get_unquoted_str(char *no_quote, size_t *i, t_data *d)
{
	size_t	i_mover;
	char	*new_portion;
	char	*unquoted;

	unquoted = x_strdup("");
	while (no_quote[*i] && !ft_strchr("\'\"*", no_quote[*i]))
	{
		i_mover = 0;
		if (no_quote[*i] == '\\' && ft_strchr("\\\'\"$", no_quote[*i + 1]))
		{
			i_mover = 2;
			new_portion = ft_substr(no_quote + *i, 1, 1);
		}
		else if (no_quote[*i] == '$')
			new_portion = variable_expansion(no_quote + *i + 1, &i_mover, d);
		else
		{
			i_mover = no_interpretation_len(no_quote + *i, NO_QUOTE);
			new_portion = ft_substr(no_quote + *i, 0, i_mover);
		}
		*i += i_mover;
		unquoted = x_strjoin_free(unquoted, new_portion, FREE_BOTH);
	}
	return (unquoted);
}
