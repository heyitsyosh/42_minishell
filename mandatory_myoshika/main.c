/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 23:27:12 by myoshika          #+#    #+#             */
/*   Updated: 2022/12/28 17:18:09 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_line(char *line, t_minishell *m)
{
	builtin_env(m);
	fflush(stdout);
	tokenize(line, m);
	// expand();
	print_tokens(m);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	m;
	char		*line;

	ft_bzero(&m, sizeof(t_minishell));
	init_envp(envp, &m);
	while (argc && argv)
	{
		//  set_signal_handlers();
		line = readline("minishell>");
		if (!line)
			break ;
		if (*line != '\0')
			add_history(line);
		execute_line(line, &m);
		free(line);
		free_tokens(m.token_head);
	}
}
