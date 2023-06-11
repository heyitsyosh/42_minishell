/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 22:31:32 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/11 20:04:00 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
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

int	builtin_exit(t_token *args)
{
	int	status;

	if (!args)
		exit(g_ms.status);
	errno = 0;
	status = ft_atoll(args->word);
	if (!str_is_numeric(args->word) || errno == ERANGE)
	{
		msg_to_stderr("exit: ", args->word, ": numeric argument required\n");
		exit(2); //why 2? check exit value in other environments
	}
	else if (args->next)
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	exit(status);
	return (EXIT_SUCCESS);
}
