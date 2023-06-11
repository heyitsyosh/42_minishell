/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 22:24:32 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/12 05:38:20 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"
#include "../../includes/minishell.h"
#include "../../includes/expand.h"
#include <dirent.h> //opendir, readdir, close_dir, DIR
#include <stdlib.h> //free

void	concat_non_asterisks(t_word *word, bool *has_wildcard)
{
	t_word	*tmp;

	while (word && word->next)
	{
		if (word->type != ASTERISK && (word->next)->type != ASTERISK)
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

bool	matches_pattern(char *d_name, t_word *word)
{
	while (word)
	{
		if ()
		word = word->next;
	}
}

t_token	*make_match_list(DIR *current_dir, t_token *head, t_token *end)
{
	char	*d_name_dup;
	t_token	*match;

	while (1)
	{
		entry = readdir(current_dir);
		if (!entry)
			break ;
		if (matches_pattern(entry->d_name, word))
		{
			d_name_dup = ft_strdup(entry->d_name);
			if (!d_name_dup)
				print_error_and_exit("strdup failure");
			match = make_token(d_name_dup, WORD);
			if (!head)
			{
				head = match;
				end = match;
			}
			else
				end->next = match;
		}
	}
	return (head);
}

t_token	*wildcard_expansion(t_word *word, t_token *next)
{
	DIR		*current_dir;
	dirent	*entry;
	t_token	*matches;

	current_dir = opendir(".");
	if (!current_dir)
		print_error_and_exit("opendir failure");
	matches = make_match_list(current_dir, NULL, NULL);
	closedir(current_dir);
	return (matches);
}

void	replace_tok_str(t_word *word, t_token *wildcard_matches, t_token *tok)
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
	t_word	*word_head;
	t_token	*wildcard_matches;
	bool	has_wildcard;

	has_wildcard = false;
	wildcard_matches = NULL;
	while (tok)
	{
		if (tok->type == WORD)
		{
			next = tok->next;
			word_head = divide_word_to_list(word);
			concat_non_asterisks(word_head, &has_wildcard);
			if (has_wildcard)
				wildcard_matches = wildcard_expansion(word_head, tok, next);
			move_word_to_token(word_head, wildcard_matches, tok);
			free_sub_word_list(word_head);
		}
		tok = next;
	}
}
