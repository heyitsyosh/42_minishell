/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_m.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 23:27:12 by myoshika          #+#    #+#             */
/*   Updated: 2022/12/12 19:06:26 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_line(char *line, t_minishell *m)
{
	tokenize(line, m);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_minishell	m;

	init_envp(&m, envp);
	while (argc && argv)
	{
		set_signal_handlers();
		line = readline("minishell>");
		if (!line)
			break ;
			// return (exit_minishell(m));
		if (*line != '\0')
			add_history(line);
		execute_line(line, &m);
		free(line);
	}
}
