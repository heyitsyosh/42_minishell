/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 22:31:32 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/08 01:01:02 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libft.h"

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

int	builtin_exit(t_token *args, t_minishell *m)
{
	int	status;

	errno = 0;
	status = ft_atoll(args->word);
	if (!str_is_numeric(args->word) || errno == ERANGE)
	{
		ft_printf("exit: %s: numeric argument required\n", args->word);
		exit (2);
	}
	else if (args->next)
	{
		ft_printf("exit: too many arguments\n");
		return (EXIT_FAILURE);
	}
	status = ft_atoi(args->word);
	exit (status);
	return (EXIT_SUCCESS);
}
