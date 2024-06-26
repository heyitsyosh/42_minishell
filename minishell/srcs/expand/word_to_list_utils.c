/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_to_list_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 22:25:30 by myoshika          #+#    #+#             */
/*   Updated: 2024/04/12 04:18:10 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h> //malloc, free

t_word	*make_sub_word(char *sub_word, t_sub_word_type type)
{
	t_word	*new_node;

	new_node = (t_word *)malloc(sizeof(t_word));
	if (!new_node)
		print_error_and_exit("malloc failure");
	new_node->sub_word = sub_word;
	new_node->type = type;
	new_node->next = NULL;
	return (new_node);
}

t_word	*ret_word_head(t_word *list_head)
{
	t_word	*word_head;

	word_head = list_head->next;
	free(list_head);
	return (word_head);
}

size_t	no_interpretation_len(char *ptr, int status)
{
	size_t	len;

	len = 0;
	while (!ft_strchr("\"$", *ptr))
	{
		if (status == NO_QUOTE && (*ptr == '\'' || *ptr == '*'))
			break ;
		if (*ptr == '\\' && ft_strchr("\\\'\"$", *(ptr + 1)))
			break ;
		ptr++;
		len++;
	}
	return (len);
}

void	free_sub_word_list(t_word *words)
{
	t_word	*tmp;

	while (words)
	{
		tmp = words;
		words = words->next;
		free(tmp->sub_word);
		free(tmp);
	}
}
