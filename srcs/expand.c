/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 04:32:24 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/11 18:25:06 by myoshika         ###   ########.fr       */
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
			new_portion = ft_substr(dquote[i], 0, 2);
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

char	*no_quote(char **no_quote_ptr, char *unquoted, size_t i)
{
	size_t		index_mover;
	char		*new_portion;
	const char	*no_quote = *no_quote_ptr;

	unquoted = ft_strdup("");
	while (no_quote[i] && no_quote[i] != '\'' && no_quote[i] != '\"')
	{
		index_mover = 0;
		if (no_quote[i] == '\\' && ft_strchr("\\\'\"$", no_quote[i + 1]))
		{
			index_mover = 2;
			new_portion = ft_substr(no_quote[i], 0, 2);
		}
		else if (no_quote[i] == '$')
			new_portion = variable_expansion(no_quote[i + 1], &index_mover);
		else
		{
			index_mover = no_interpretation_len(no_quote[i], NOT_IN_DQUOTE);
			new_portion = ft_substr(no_quote[i], 0, index_mover);
		}
		i += index_mover;
		unquoted = ft_strjoin_with_free(unquoted, new_portion, FREE_BOTH);
	}
	*no_quote_ptr += i;
	return (unquoted);
}

void	variable_expansion_loop(t_token *tok, bool *has_wildcard_expansion)
{
	char	*word;
	char	*new_portion;
	char	*expanded;

	word = tok->word;
	expanded = ft_calloc(1, sizeof(char *));
	while (*word)
	{
		if (*word == '\'')
			new_portion = quote(&word);
		else if (*word == '\"')
			new_portion = dquote(&word, NULL, 1);
		else
		{
			new_portion = no_quote(&word, NULL, 0);
			if (ft_strchr(new_portion, '*'))
				*has_wildcard_expansion = true;
		}
		expanded = ft_strjoin_with_free(expanded, new_portion, FREE_BOTH);
	}
	free(tok->word);
	tok->word = expanded;
}

void	expand(t_token *tok)
{
	bool	has_wildcard_expansion;
	t_token	*next;

	while (tok)
	{
		has_wildcard_expansion = false;
		if (tok->type == WORD)
		{
			next = tok->next;
			variable_expansion_loop(tok, &has_wildcard_expansion);
		//	if (has_wildcard_expansion)
		// 	wildcard_expansion(tok);
			quote_removal_loop(tok);
		}
		tok = next;
	}
}

//might do word splitting and emulate parameters in heredoc