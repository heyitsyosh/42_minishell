/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 00:55:19 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/19 06:01:08 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include <limits.h> //INT_MAX
#include <stdlib.h> //malloc

bool	is_blank(char c)
{
	return (c == ' ' || c == '\t');
}

bool	is_operator(char c)
{
	return (c && ft_strchr("|&()<>", c));
}

bool	is_io_number(char *line)
{
	long	io_num;
	char	*endptr;

	if (!ft_isdigit(*line))
		return (false);
	io_num = ft_strtol(line, &endptr, 10);
	if (io_num > INT_MAX)
		return (false);
	if (!endptr || (*endptr != '<' && *endptr != '>'))
		return (false);
	return (true);
}

t_token_type	get_operator_type(char *operator)
{
	if (!ft_strcmp(operator, "&&"))
		return (AND);
	else if (!ft_strcmp(operator, "||"))
		return (OR);
	else if (!ft_strcmp(operator, ">>"))
		return (REDIRECT_APPEND);
	else if (!ft_strcmp(operator, "<<"))
		return (REDIRECT_HEREDOC);
	else if (!ft_strcmp(operator, "<"))
		return (REDIRECT_IN);
	else if (!ft_strcmp(operator, ">"))
		return (REDIRECT_OUT);
	else if (!ft_strcmp(operator, "("))
		return (OPEN_PARENTHESIS);
	else if (!ft_strcmp(operator, ")"))
		return (CLOSE_PARENTHESIS);
	else if (!ft_strcmp(operator, "|"))
		return (PIPE);
}

t_token	*make_token(char *word, t_token_type type)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		print_error_and_exit("malloc failure");
	new->word = word;
	new->type = type;
	new->next = NULL;
	return (new);
}
