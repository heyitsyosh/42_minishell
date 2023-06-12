/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 05:49:26 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/13 06:06:10 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/expand.h"
#include "../../includes/libft.h"
#include <sys/types.h> //struct dirent
#include <dirent.h> //opendir, readdir, close_dir, DIR

bool	matches_pattern(char *d_name, t_word *word)
{
	bool	active_wildcard;
	char	*ptr_to_matching_substr;

	active_wildcard = false;
	while (word)
	{
		if (word->type == WILDCARD)
			active_wildcard = true;
		else
		{
			if (active_wildcard)
				ptr_to_matching_substr = ft_strstr(d_name, word->sub_word);
			else
				if (ft_strncmp(d_name, word->sub_word, ft_strlen(word->sub_word)))
					ptr_to_matching_substr = NULL;
			if (!ptr_to_matching_substr)
				return (false);
			d_name = ptr_to_matching_substr;
			active_wildcard = false;
		}
		word = word->next;
	}
	return (true);
}

t_token	*make_match_list(DIR *current_dir, t_word *word)
{
	struct dirent	*entry;
	char			*d_name_dup;
	t_token			*match;
	t_token			*head;
	t_token			*end;

	head = NULL;
	end = NULL;
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
	t_token	*matches;

	current_dir = opendir(".");
	if (!current_dir)
		print_error_and_exit("opendir failure");
	matches = make_match_list(current_dir, word);
	closedir(current_dir);
	if (!matches)
	{
		matches = make_token(ft_strdup(""), WORD);
		if (!matches->word)
			print_error_and_exit("strdup failure");
	}
	return (matches);
}
