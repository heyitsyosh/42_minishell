/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 05:49:26 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/12 06:51:38 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/expand.h"
#include "../../includes/libft.h"
#include <dirent.h> //opendir, readdir, close_dir, DIR

bool	matches_pattern(char *d_name, t_word *word)
{

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
	if (!matches)
	{
		matches = make_token(ft_strdup(""), WORD);
		if (!matches->sub_word)
			print_error_and_exit("strdup failure");
	}
	return (matches);
}
