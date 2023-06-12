/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_to_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 19:11:22 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/13 06:07:43 by myoshika         ###   ########.fr       */
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
	t_word	*quoted_node;
	char	*quoted_sub_str;

	i = 1;
	quoted_sub_str = get_quoted_str(*quote_ptr, &i);
	if (!quoted_sub_str)
		print_error_and_exit("malloc failure");
	if ((*quote_ptr)[i] == '\'')
		quoted_node = make_sub_word_node(quoted_sub_str, QUOTED);
	else
	{
		free(quoted_sub_str);
		quoted_sub_str = ft_strdup("\'");
		if (!quoted_sub_str)
			print_error_and_exit("strdup failure");
		quoted_node = make_sub_word_node(quoted_sub_str, UNQUOTED);
		i = 0;
	}
	*quote_ptr += i + 1;
	return (quoted_node);
}

static t_word	*dquote(char **dquote_ptr)
{
	size_t	i;
	t_word	*dquoted_node;
	char	*dquoted_sub_str;

	i = 1;
	dquoted_sub_str = get_dquoted_str(*dquote_ptr, &i);
	if (!dquoted_sub_str)
		print_error_and_exit("malloc failure");
	if ((*dquote_ptr)[i] == '\"')
		dquoted_node = make_sub_word_node(dquoted_sub_str, DQUOTED);
	else
	{
		free(dquoted_sub_str);
		dquoted_sub_str = ft_strdup("\"");
		if (!dquoted_sub_str)
			print_error_and_exit("strdup failure");
		dquoted_node = make_sub_word_node(dquoted_sub_str, UNQUOTED);
		i = 0;
	}
	*dquote_ptr += i + 1;
	return (dquoted_node);
}

static t_word	*wildcard(char **word)
{
	char	*wildcard;
	t_word	*wildcard_word;

	wildcard = ft_strdup("*");
	if (!wildcard)
		print_error_and_exit("strdup failure");
	wildcard_word = make_sub_word_node(wildcard, WILDCARD);
	*word += 1;
	return (wildcard_word);
}

static t_word	*no_quote(char **no_quote_ptr)
{
	size_t	i;
	t_word	*unquoted_node;
	char	*unquoted_sub_str;

	i = 0;
	unquoted_sub_str = get_unquoted_str(*no_quote_ptr, &i);
	*no_quote_ptr += i;
	if (!unquoted_sub_str)
		print_error_and_exit("malloc failure");
	unquoted_node = make_sub_word_node(unquoted_sub_str, UNQUOTED);
	return (unquoted_node);
}

t_word	*divide_word_to_list(char *word)
{
	t_word	*sub_word;
	t_word	*list_head;
	t_word	*last_sub_word;

	list_head = make_sub_word_node(NULL, HEAD);
	last_sub_word = list_head;
	while (*word)
	{
		if (*word == '\'')
			sub_word = quote(&word);
		else if (*word == '\"')
			sub_word = dquote(&word);
		else if (*word == '*')
			sub_word = wildcard(&word);
		else
			sub_word = no_quote(&word);
		last_sub_word->next = sub_word;
	}
	return (ret_word_head(list_head));
}
