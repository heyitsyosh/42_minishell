/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 21:45:51 by myoshika          #+#    #+#             */
/*   Updated: 2023/09/08 15:56:25 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"
#include "../../includes/minishell.h"
#include "../../includes/ft_printf.h"
#include <unistd.h> //STDERR_FILENO
#include <stdlib.h> //exit

void	print_error_and_exit(char *error_message)
{
	ft_dprintf(STDERR_FILENO, "minishell: %s\n", error_message);
	exit(1);
}

void	print_syntax_error(char *unexpected_token)
{
	ft_dprintf(STDERR_FILENO, \
		"syntax error near unexpected token `%s'\n", unexpected_token);
}

void	err_msg(char *s1, char *s2, char *s3)
{
	char	*joined;

	if (s1)
		joined = x_strdup(s1);
	if (s2)
		joined = x_strjoin_free(joined, s2, FREE_FIRST);
	if (s3)
		joined = x_strjoin_free(joined, s3, FREE_FIRST);
	if (joined)
		joined = x_strjoin_free(joined, "\n", FREE_FIRST);
	ft_dprintf(STDERR_FILENO, "%s", joined);
	free(joined);
}
