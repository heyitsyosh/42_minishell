/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 22:24:32 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/13 06:30:53 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"
#include "../../includes/minishell.h"
#include "../../includes/expand.h"
#include <stdlib.h> //free

void	concat_non_asterisks(t_word *word, bool *has_wildcard)
{
	t_word	*tmp;

	while (word && word->next)
	{
		if (word->type != WILDCARD && (word->next)->type != WILDCARD)
		{
			word->sub_word = ft_strjoin_with_free(word->sub_word, \
				(word->next)->sub_word, FREE_BOTH);
			tmp = word->next->next;
			free((word->next)->sub_word);
			free(word->next);
			word->next = tmp;
		}
		else
		{
			*has_wildcard = true;
			word = word->next;
		}
	}
}

void	replace_token_with_expanded(t_word *word, t_token *wildcard_matches, t_token *tok)
{
	t_token	*next;

	if (wildcard_matches)
	{
		next = tok->next;
		free(tok);
		tok = wildcard_matches;
		while (tok->next != NULL)
			tok = tok->next;
		tok->next = next;
	}
	else
	{
		free(tok->word);
		tok->word = word->sub_word;
		free(word);
	}
}

void	expand(t_token *tok)
{
	t_token	*next;
	t_token	*wildcard_matches;
	t_word	*word_head;
	bool	has_wildcard;

	has_wildcard = false;
	wildcard_matches = NULL;
	while (tok)
	{
		if (tok->type == WORD)
		{
			next = tok->next;
			word_head = divide_word_to_list(tok->word);
			concat_non_asterisks(word_head, &has_wildcard);
			if (has_wildcard)
				wildcard_matches = wildcard_expansion(word_head, tok);
			replace_token_with_expanded(word_head, wildcard_matches, tok);
			free_sub_word_list(word_head);
		}
		tok = next;
	}
}
