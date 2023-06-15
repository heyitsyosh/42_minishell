/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 21:45:51 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/14 07:57:24 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include <unistd.h> //STDERR_FILENO
#include <stdlib.h> //exit

void	print_error_and_exit(char *error_message)
{
	ft_putstr_fd(error_message, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	exit(1);
}

void	print_syntax_error(char *unexpected_token)
{
	ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
	ft_putstr_fd(unexpected_token, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
}

void	msg_to_stderr(char *first, char *second, char *third)
{
	if (first)
		ft_putstr_fd(first, STDERR_FILENO);
	if (second)
		ft_putstr_fd(second, STDERR_FILENO);
	if (third)
		ft_putstr_fd(third, STDERR_FILENO);
}
