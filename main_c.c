/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshono <cshono@student.42.tokyo>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 21:05:41 by cshono            #+#    #+#             */
/*   Updated: 2022/12/13 17:30:52 by cshono           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char **envp)
{
	char 		*str;
	t_prompt	prompt;
	while (argv && argc)
	{
		str = readline("minishell $ ");
		if (!check_args(str, &prompt))
			break;
	}
	exit()
}