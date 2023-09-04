/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 22:31:32 by myoshika          #+#    #+#             */
/*   Updated: 2023/09/04 22:20:40 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/ft_printf.h"
#include "../../includes/libft.h"
#include <stdlib.h> //exit, EXIT_SUCCESS, EXIT_FAILURE
#include <unistd.h> //STDERR_FILENO
#include <errno.h> //errno, ERANGE

static bool	str_is_numeric(char *str)
{
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

int	builtin_exit(t_token *args, t_data *d)
{
	int	status;

	if (!args)
		exit(d->exit_status);
	errno = 0;
	status = ft_atoll(args->word);
	if (!str_is_numeric(args->word) || errno == ERANGE)
	{
		ft_dprintf(STDERR_FILENO, \
			"exit: %s: numeric argument required\n", args->word);
		exit(2);
	}
	else if (args->next)
	{
		ft_dprintf(STDERR_FILENO, "exit: too many arguments\n");
		return (EXIT_FAILURE);
	}
	exit(status);
	return (EXIT_SUCCESS);
}
