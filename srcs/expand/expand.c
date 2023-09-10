/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 22:24:32 by myoshika          #+#    #+#             */
/*   Updated: 2023/09/11 04:08:36 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"
#include "../../includes/minishell.h"
#include <stdlib.h> //free

void	concat_non_asterisks(t_word *word, bool *has_wildcard)
{
	t_word	*tmp;

	if (word && word->type == WILDCARD)
		*has_wildcard = true;
	while (word && word->next)
	{
		if (word->type != WILDCARD && (word->next)->type != WILDCARD)
		{
			word->sub_word = x_strjoin_free(word->sub_word, \
				(word->next)->sub_word, FREE_BOTH);
			tmp = word->next->next;
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

static void	insert_wildcards_to_list(\
		t_token *wildcard, t_token *current, t_token *saved_next)
{
	t_token	*wildcard_head;
	t_token	*wildcard_tail;

	wildcard_head = wildcard;
	wildcard_tail = wildcard;
	while (wildcard_tail->next)
		wildcard_tail = wildcard_tail->next;
	wildcard_tail->next = saved_next;
	free(current->word);
	current->word = wildcard->word;
	current->next = wildcard->next;
	free(wildcard_head);
}

static void	replace_with_expanded(t_word *word, t_token *current)
{
	free(current->word);
	current->word = x_strdup(word->sub_word);
}

void	expand(t_token *tok, t_data *d)
{
	t_token	*saved_next;
	t_token	*wildcard_matches;
	t_word	*word_head;
	bool	has_wildcard;

	while (tok)
	{
		saved_next = tok->next;
		if (tok->type == WORD)
		{
			has_wildcard = false;
			word_head = divide_word_to_list(tok->word, d);
			concat_non_asterisks(word_head, &has_wildcard);
			if (has_wildcard)
			{
				wildcard_matches = wildcard_expansion(word_head);
				insert_wildcards_to_list(wildcard_matches, tok, saved_next);
			}
			else
				replace_with_expanded(word_head, tok);
			free_sub_word_list(word_head);
		}
		tok = saved_next;
	}
}
