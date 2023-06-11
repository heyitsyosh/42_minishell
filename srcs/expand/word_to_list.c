/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 19:11:22 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/11 22:20:51 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/expand.h"
#include "../includes/libft.h"
#include "../includes/get_next_line.h"

t_word	*make_sub_word_node(char *sub_word, e_sub_word_type type)
{
	t_word	*new_node;

	new_node = (t_word *)malloc(sizeof(t_word));
	if (!new_node)
		print_error_and_exit("malloc failure");
	new_word->sub_word = sub_word;
	new_word->type = type;
	new_word->next = NULL;
	return (new_node);
}

t_word	*ret_word_head(t_word *list_head)
{
	t_word	*word_head;

	word_head = list_head->next;
	free(list_head);
	return (word_head);
}

t_word	*wildcard(char **word)
{
	t_char	*wildcard;
	t_word	*wildcard_word;

	wildcard = ft_strdup("*");
	if (!asterisk)
		print_error_and_exit("strdup failure");
	wildcard_word = make_sub_word(wildcard, WILDCARD);
	*word += 1;
	return (wildcard_word);
}

char	*get_unquoted_str(char *no_quote, size_t *i)
{
	size_t		index_mover;
	char		*new_portion;

	unquoted = ft_strdup("");
	while (no_quote[i])
	{
		index_mover = 0;
		if (no_quote[i] != '\'' && no_quote[i] != '\"' && no_quote[i] != '*')
			break ;
		if (no_quote[i] == '\\' && ft_strchr("\\\'\"$", no_quote[i + 1]))
		{
			index_mover = 2;
			new_portion = ft_substr(no_quote[i], 1, 1);
		}
		else if (no_quote[i] == '$')
			new_portion = variable_expansion(no_quote[i + 1], &index_mover);
		else
		{
			index_mover = no_interpretation_len(no_quote[i], NOT_IN_DQUOTE);
			new_portion = ft_substr(no_quote[i], 0, index_mover);
		}
		*i += index_mover;
		unquoted = ft_strjoin_with_free(unquoted, new_portion, FREE_BOTH);
	}
	return (unquoted);
}

t_word	*no_quote(char **no_quote_ptr)
{
	size_t	i;
	t_word	*unquoted_node;
	t_char	*unquoted_sub_str;

	i = 0;
	unquoted_sub_str = get_unquoted_str(*no_quote_ptr, &i);
	*no_quote_ptr += i;
	if (!unquoted_sub_str)
		print_error_and_exit("malloc failure");
	unquoted_node = make_sub_word_node(unquoted_sub_str, UNQUOTED);
	return (unquoted_node);
}

t_word	*quote(char **quote_ptr)
{
	size_t	i;
	t_word	*quoted_node;
	t_char	*quoted_sub_str;

	i = 0;
	quoted_sub_str = get_unquoted_str(*quote_ptr, &i);
	*quote_ptr += i;
	if (!quoted_sub_str)
		print_error_and_exit("malloc failure");
	quoted_node = make_sub_word_node(quoted_sub_str, UNQUOTED);
	return (quoted_node);
}

t_word	*dquote(char **dquote_ptr)
{
	size_t	i;
	t_word	*dquoted_node;
	t_char	*dquoted_sub_str;

	i = 0;
	dquoted_sub_str = get_dquoted_str(*dquote_ptr, &i);
	*dquote_ptr += i;
	if (!dquoted_sub_str)
		print_error_and_exit("malloc failure");
	dquoted_node = make_sub_word_node(dquoted_sub_str, UNQUOTED);
	return (dquoted_node);
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
			sub_word = dquote(&word, NULL, 1);
		else if (*word == '*')
			sub_word = wildcard(&word);
		else
			sub_word = no_quote(&word, NULL, 0);
		last_sub_word->next = sub_word;
	}
	return (ret_word_head(list_head));
}

void	expand(t_token *tok)
{
	bool	has_wildcard_expansion;
	t_token	*next;
	t_word	*word_head;

	while (tok)
	{
		has_wildcard_expansion = false;
		if (tok->type == WORD)
		{
			// next = tok->next;
			word_head = divide_word_to_list(word);
			// variable_expansion_loop(tok, &has_wildcard_expansion);
			// if (has_wildcard_expansion)
			// 	wildcard_expansion(tok);
			// concat_list_to_word(tok);
		}
		tok = next;
	}
}
