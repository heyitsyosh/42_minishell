/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 21:45:51 by myoshika          #+#    #+#             */
/*   Updated: 2023/09/04 22:24:57 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/ft_printf.h"
#include "../../includes/libft.h"
#include <unistd.h> //STDERR_FILENO
#include <stdlib.h> //exit

void	print_error_and_exit(char *error_message)
{
	ft_dprintf(STDERR_FILENO, "minishell: %s\n", error_message);
	exit(1);
}

void	print_syntax_error(char *unexpected_token)
{
	ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
	ft_putstr_fd(unexpected_token, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
}
