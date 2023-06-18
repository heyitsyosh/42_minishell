/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 01:58:27 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/19 02:18:09 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft.h"

void	print_tokens(t_token *head)
{
	while (head->next)
	{
		printf("%s->", head->word);
		head = head->next;
	}
	if (head)
	printf("[%s]\n", head->word);
}
