/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:07:51 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/12 02:24:08 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/expand.h"
#include <stdlib.h> //free

void	free_tokens(t_token *tok)
{
	t_token	*tmp;

	while (tok)
	{
		tmp = tok;
		tok = tok->next;
		free(tmp->word);
		free(tmp);
	}
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

// void	free_nodes(t_node *nodes)
// {
// 	t_node	*tmp;

// 	while (nodes)
// 	{
// 		tmp = nodes;
// 		nodes = nodes->next;
// 		free (tmp);
// 	}
// }
