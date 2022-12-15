/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 04:35:25 by myoshika          #+#    #+#             */
/*   Updated: 2022/12/16 00:44:02 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*extract_token(char	*cursor)
{
	if (*cursor == )
}

static size_t	fill_token_info(t_token *node, char *cursor)
{
	size_t	token_len;

	token_len = 0;
	node->token = extract_token(cursor);
	if (node->token)
		token_len = ft_strlen(node->token);
	node->type = determine_type(node->token);
	node->next = NULL;
	node->prev = NULL;
	return (token_len);
}

void	tokenize(char *line, t_minishell *m)
{
	size_t	i;
	t_token	*new_token;

	i = 0;
	while (line[i])
	{
		new_token = malloc(sizeof(t_token));
		// if (!new_node)
		// 	error handle
		i += fill_token_info(new_node, line[i]);
		// if (!new_node->token)
			// error handle
		
	}
}

	// <
	// <<
	// >>
	// >
	// |
	// ||
	// &&
	// ()
	// ""
	// ''
	
	/*
	${PWD} $(PWD) $[PWD]
	< (echo "a" || cat "b")
	*/