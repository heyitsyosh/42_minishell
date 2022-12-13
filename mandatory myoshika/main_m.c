/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_m.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshono <cshono@student.42.tokyo>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 23:27:12 by myoshika          #+#    #+#             */
/*   Updated: 2022/12/13 18:42:27 by cshono           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_safe_free(char **pointer)
{
	if (*pointer)
	{
		free(*pointer);
		*pointer = NULL;
	}
}


void	execute_line(char *line, t_minishell *m)
{
	tokenize(line, m);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_minishell	m;

	init_envp(&m, envp);//t_minishell m, 環境変数を渡す
	while (argc && argv)
	{
		set_signal_handlers();
		line = readline("minishell>");
		if (!line)
			break ;
			return (exit_minishell(m));
		if (*line != '\0')
			add_history(line);
		execute_line(line, &m);
		free(line);
	}
}
