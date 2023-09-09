/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 05:49:26 by myoshika          #+#    #+#             */
/*   Updated: 2023/09/10 01:37:01 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"
#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include <sys/types.h> //struct dirent
#include <dirent.h> //opendir, readdir, close_dir, DIR

static t_token	*make_match_list(DIR *current_dir, t_word *word)
{
	struct dirent	*entry;
	t_token			*match;
	t_token			head;

	head.next = NULL;
	match = &head;
	while (1)
	{
		entry = readdir(current_dir);
		if (!entry)
			break ;
		if (entry->d_name[0] != '.' && matches_pattern(entry->d_name, word))
		{
			match->next = make_token(x_strdup(entry->d_name), WORD);
			match = match->next;
		}
	}
	return (head.next);
}

static char	*concat_subwords(t_word *word)
{
	char	*concatenated;

	concatenated = x_strdup("");
	while (word)
	{
		concatenated = x_strjoin_free(concatenated, word->sub_word, FREE_FIRST);
		word = word->next;
	}
	return (concatenated);
}

t_token	*wildcard_expansion(t_word *word)
{
	DIR		*current_dir;
	t_token	*matches;

	current_dir = opendir(".");
	if (!current_dir)
		print_error_and_exit("opendir failure");
	matches = make_match_list(current_dir, word);
	closedir(current_dir);
	if (!matches)
		matches = make_token(concat_subwords(word), WORD);
	return (matches);
}
