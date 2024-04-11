/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 22:53:59 by myoshika          #+#    #+#             */
/*   Updated: 2024/04/12 04:19:25 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_printf.h"
#include "libft.h"
#include <stdlib.h> //EXIT_SUCCESS

int	builtin_echo(t_token *args, t_data *d)
{
	bool	new_line;

	(void)d;
	new_line = true;
	if (args && !ft_strcmp(args->word, "-n"))
	{
		new_line = false;
		while (args && !ft_strcmp(args->word, "-n"))
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
