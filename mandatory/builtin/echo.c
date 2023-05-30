/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 22:53:59 by myoshika          #+#    #+#             */
/*   Updated: 2023/05/30 17:12:06 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_echo(t_token *args, bool new_line)
{
	if (str)
		ft_printf("%s", str);
	else
		return (EXIT_FAILURE);
	if (new_line)
		ft_printf("\n");
	return (EXIT_SUCCESS);
}

//space between echo parameters??