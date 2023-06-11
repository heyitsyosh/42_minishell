/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 19:11:22 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/11 19:11:38 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft.h"
#include "../includes/get_next_line.h"

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
			next = tok->next;
			word_head = divide_word_to_list();
			variable_expansion_loop(tok, &has_wildcard_expansion);
			if (has_wildcard_expansion)
				wildcard_expansion(tok);
			quote_removal_loop(tok);
		}
		tok = next;
	}
}