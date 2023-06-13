/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 22:23:03 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/13 08:50:09 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

typedef enum e_sub_word_type
{
	QUOTED,
	DQUOTED,
	UNQUOTED,
	WILDCARD,
	HEAD,
}	t_sub_word_type;

typedef struct s_word
{
	char			*sub_word;
	t_sub_word_type	type;
	struct s_word	*next;
}	t_word;

/* word_to_list.c */
t_word	*divide_word_to_list(char *word);

/* word_to_list_ii.c */
char	*get_quoted_str(char *quote, size_t *i);
char	*get_dquoted_str(char *dquote, size_t *i);
char	*get_unquoted_str(char *no_quote, size_t *i);

/* word_to_list_util.c */
t_word	*make_sub_word_node(char *sub_word, t_sub_word_type type);
t_word	*ret_word_head(t_word *list_head);
size_t	no_interpretation_len(char *ptr, int status);

/* variable_expansion.c */
char	*variable_expansion(char *ptr, size_t *index_mover);

/* wildcard_expansion.c */
t_token	*wildcard_expansion(t_word *word, t_token *next);

/* free.c */
void	free_sub_word_list(t_word *words);

#endif