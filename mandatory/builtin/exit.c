/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 22:31:32 by myoshika          #+#    #+#             */
/*   Updated: 2023/05/31 01:47:42 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libft.h"

static bool	str_is_numeric(char *str)
{
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

	if (!str_is_numeric(args->word))
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

//why is it exit (2)? must be some reason