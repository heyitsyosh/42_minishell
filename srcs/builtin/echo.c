/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 22:53:59 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/24 17:55:33 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/ft_printf.h"
#include "../../includes/libft.h"
#include <stdlib.h> //EXIT_SUCCESS

int	builtin_echo(t_token *args)
{
	bool	new_line;

	new_line = true;
	if (args && !ft_strcmp(args->word, "-n"))
	{
		new_line = false;
		args = args->next;
	}
	while (args)
	{
		ft_printf("%s", args->word);
		if (args->next && *args->next->word)
			ft_printf(" ");
		args = args->next;
	}
	if (new_line)
		ft_printf("\n");
	return (EXIT_SUCCESS);
}
