/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeninze_ii.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 21:59:16 by myoshika          #+#    #+#             */
/*   Updated: 2022/12/21 20:12:53 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*extract_operator_token_ii(char *cursor, t_token *t)
{
	if (t->type == GREATER && cursor[1] == '>')
	{
		t->type = APPEND;
		return (ft_strdup(">>"));
	}
	else if (t->type == GREATER)
		return (ft_strdup(">"));
	else if (t->type == LESSER && cursor[1] == '<')
	{
		t->type = HEREDOC;
		return (ft_strdup("<<"));
	}
	else if (t->type == LESSER)
		return (ft_strdup("<"));
	return (NULL);
}

char	*extract_operator_token(char *cursor, t_token *t)
{
	if (t->type == AND)
		return (ft_strdup("&&"));
	else if (t->type == LEFT_PARENTHESIS)
		return (ft_strdup("("));
	else if (t->type == RIGHT_PARENTHESIS)
		return (ft_strdup(")"));
	else if (t->type == PIPE && cursor[1] == '|')
	{
		t->type = OR;
		return (ft_strdup("||"));
	}
	else if (t->type == PIPE)
		return (ft_strdup("|"));
	return (extract_operator_token_ii(cursor, t));
}
