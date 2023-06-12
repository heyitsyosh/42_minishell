/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 19:11:38 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/13 08:28:16 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libft.h"

#include <stdio.h>
t_token	*operator(char *line)
{
	int			i;
	char		*operator;
	const char	*operators[] = \
	{"&&", "||", "<<", ">>", "<", ">", "|", "(", ")", NULL};

	i = 0;
	while (ft_strncmp(operators[i], line, ft_strlen(operators[i])))
		i++;
	operator = ft_strdup(operators[i]);
	if (!operator)
		print_error_and_exit("strdup failure");
	return (make_token(operator, get_operator_type(operator)));
}

size_t	count_till_closing_quote(char *start_of_quote)
{
	size_t	len;

	len = 1;
	while (start_of_quote[len] && !is_blank(start_of_quote[len]) \
		&& start_of_quote[0] != start_of_quote[len])
	{
		if (start_of_quote[0] == '\"' \
			&& start_of_quote[len] == '\\' && start_of_quote[len + 1] == '\"')
			len++;
		len++;
	}
	if (*(start_of_quote + len) == *start_of_quote)
		len++;
	return (len);
}

t_token	*word(char *line)
{
	char	*word;
	size_t	word_len;

	word_len = 0;
	while (line[word_len] && \
		!is_blank(line[word_len]) && !is_operator(line[word_len]))
	{
		if (line[word_len] == '\'' || line[word_len] == '\"')
			word_len += count_till_closing_quote(&line[word_len]);
		else
			word_len++;
	}
	word = ft_substr(line, 0, word_len);
	if (!word)
		print_error_and_exit("substr failure");
	return (make_token(word, WORD));
}

t_token	*io_number(char *line)
{
	char	*io_number;
	size_t	len;

	len = 0;
	while (ft_isdigit(line[len]))
		len++;
	io_number = ft_substr(line, 0, len);
	if (!io_number)
		print_error_and_exit("substr failure");
	return (make_token(io_number, IO_NUMBER));
}

t_token	*tokenize(char *line)
{
	t_token	*tok;
	t_token	head;

	tok = &head;
	while (*line)
	{
		while (is_blank(*line))
			line++;
		if (is_operator(*line))
			tok->next = operator(line);
		else if (is_io_number(line))
			tok->next = io_number(line);
		else
			tok->next = word(line);
		tok = tok->next;
		line += ft_strlen(tok->word);
	}
	return (head.next);
}
