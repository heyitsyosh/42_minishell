/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:26:06 by myoshika          #+#    #+#             */
/*   Updated: 2023/05/24 00:31:15 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h> //STDERR_FILENO
#include <stdlib.h> //getenv

volatile sig_atomic_t	g_status;

void	run_commands(char *line, t_minishell *m)
{
	t_token		*tok;

	tok = tokenize(line);
	parser(&tok);
	/*
	if (!error)
	{
		//expand(node);
		set_up_redirect(node);
		execute(node);
		reset_redirect(node);
	}
	else
		set_exit_status
	*/
	free_tokens(tok);
}

void	minishell_loop(t_minishell	*m)
{
	char	*line;

	m->is_interactive_mode = true;
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (*line)
		{
			add_history(line);
			run_commands(line, m);
			free(line);
		}
	}
}

void	run_one_line(int argc, char **argv, t_minishell	*m)
{
	m->is_interactive_mode = false;
	if (argc == 2)
	{
		ft_putstr_fd("bash: -c: option requires an argument\n", STDERR_FILENO);
		exit(2);
	}
	if (ft_strlen(argv[2]) != 0)
		run_commands(argv[2], m);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	m;
	//rl_outstream = stderr;
	init_envp(envp, &m);
	if (argc >= 2 && !ft_strcmp("-c", argv[1]))
		run_one_line(argc, argv, &m);
	else
		minishell_loop(&m);
	exit(g_status);
}
