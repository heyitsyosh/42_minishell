/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 17:24:46 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/11 18:12:43 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft.h"

char	*remove_quote(char **quote_ptr)
{
	size_t		i;
	size_t		inside_quote_len;
	char		*quoted;
	const char	*quote = *quote_ptr;

	i = 1;
	inside_quote_len = 0;
	while (quote[i] && quote[i] != '\'')
	{
		i++;
		inside_quote_len++;
	}
	if (quote[i] == '\'')
		i++;
	quoted = ft_substr(quote, 1, inside_quote_len);
	if (!quoted)
		print_error_and_exit("substr failure");
	*quote_ptr += i;
	return (quoted);
}

char	*remove_dquote(char **dquote_ptr, char *dquoted, size_t i)
{
	size_t		index_mover;
	char		*new_portion;
	char		*dquoted;
	const char	*dquote = *dquote_ptr;

	dquoted = ft_strdup("");
	while (dquote[i] && dquote[i] != '\"')
	{
		
	}
	return (dquoted);
}

void	quote_removal_loop(t_token *tok)
{
	char	*word;
	char	*new_portion;
	char	*removed;

	word = tok->word;
	removed = ft_calloc(1, sizeof(char *));
	while (*word)
	{
		if (*word == '\'')
			new_portion = remove_quote(&word);
		else if (*word == '\"')
			new_portion = remove_dquote(&word, ft_strdup(""), 1);
		else
			new_portion = no_quote(&word, ft_strdup(""), 0);
		removed = ft_strjoin_with_free(removed, new_portion, FREE_BOTH);
	}
	free(tok->word);
	tok->word = removed;
}
