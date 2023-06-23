/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_to_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 19:11:22 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/23 11:25:13 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"
#include "../../includes/minishell.h"
#include "../../includes/expand.h"
#include "../../includes/libft.h"
#include <stdlib.h> //free

static t_word	*quote(char **quote_ptr)
{
	size_t	i;
	char	*quoted_str;
	t_word	*quoted_node;

	i = 1;
	quoted_str = get_quoted_str(*quote_ptr, &i);
	if (!quoted_str)
		print_error_and_exit("malloc failure");
	if ((*quote_ptr)[i] == '\'')
		quoted_node = make_sub_word_node(quoted_str, QUOTED);
	else
	{
		free(quoted_str);
		quoted_str = xstrdup("\'");
		quoted_node = make_sub_word_node(quoted_str, UNQUOTED);
		i = 0;
	}
	*quote_ptr += i + 1;
	return (quoted_node);
}

static t_word	*dquote(char **dquote_ptr)
{
	size_t	i;
	char	*dquoted_str;
	t_word	*dquoted_node;

	i = 1;
	dquoted_str = get_dquoted_str(*dquote_ptr, &i);
	if (!dquoted_str)
		print_error_and_exit("malloc failure");
	if ((*dquote_ptr)[i] == '\"')
		dquoted_node = make_sub_word_node(dquoted_str, DQUOTED);
	else
	{
		free(dquoted_str);
		dquoted_str = xstrdup("\"");
		dquoted_node = make_sub_word_node(dquoted_str, UNQUOTED);
		i = 0;
	}
	*dquote_ptr += i + 1;
	return (dquoted_node);
}

static t_word	*wildcard(char **wildcard_ptr)
{
	char	*wildcard_str;
	t_word	*wildcard_node;

	wildcard_str = xstrdup("*");
	wildcard_node = make_sub_word_node(wildcard_str, WILDCARD);
	*wildcard_ptr += 1;
	return (wildcard_node);
}

static t_word	*no_quote(char **no_quote_ptr)
{
	size_t	i;
	char	*unquoted_str;
	t_word	*unquoted_node;

	i = 0;
	unquoted_str = get_unquoted_str(*no_quote_ptr, &i);
	if (!unquoted_str)
		print_error_and_exit("malloc failure");
	unquoted_node = make_sub_word_node(unquoted_str, UNQUOTED);
	*no_quote_ptr += i;
	return (unquoted_node);
}

t_word	*divide_word_to_list(char *word)
{
	t_word	head;
	t_word	*sub_word;

	sub_word = &head;
	while (*word)
	{
		if (*word == '\'')
			sub_word->next = quote(&word);
		else if (*word == '\"')
			sub_word->next = dquote(&word);
		else if (*word == '*')
			sub_word->next = wildcard(&word);
		else
			sub_word->next = no_quote(&word);
		sub_word = sub_word->next;
	}
	return (head.next);
}
