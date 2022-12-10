/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 23:27:12 by myoshika          #+#    #+#             */
/*   Updated: 2022/12/09 18:09:22 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_minishell	m;

	while (argc && argv)
	{
		signal_handling();
		line = readline("minishell>");
		if (!line)
			return (exit_minishell(m));
		if (*line != '\0')
			add_history(line);
		lexer(line, &m);
		parser(&m);
		free(line);
	}
	exit();
}
