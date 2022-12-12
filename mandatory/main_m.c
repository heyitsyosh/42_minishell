/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_m.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 23:27:12 by myoshika          #+#    #+#             */
/*   Updated: 2022/12/12 18:22:05 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	unset(char *id, m)
// {
	
// }

execute_line(char *line, t_minishell *m)
{
	
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_minishell	m;

	init_shell(&m, envp);
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
