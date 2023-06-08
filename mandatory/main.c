/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:26:06 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/09 05:34:49 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h> //STDERR_FILENO

t_minishell g_ms;

void	run_commands(char *line)
{
	t_token		*tok;
	t_parse		*p;

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
	free(p);
	free_tokens(tok);
}

void	minishell_loop(void)
{
	char	*line;

	g_ms.is_interactive_mode = true;
	while (1)
	{
		setup_parent_signal_handler();
		line = readline("> ");
		if (!line)
			break ;
		if (*line)
		{
			add_history(line);
			run_commands(line);
			free(line);
		}
		if (g_ms.signum == SIGINT)
			ft_printf("\n");
	}
	ft_printf("exit\n");
}

void	run_one_line(int argc, char **argv)
{
	g_ms.is_interactive_mode = false;
	if (argc == 2)
	{
		ft_putstr_fd("bash: -c: option requires an argument\n", STDERR_FILENO);
		exit(2);
	}
	if (ft_strlen(argv[2]) != 0)
		run_commands(argv[2]);
}

//default execution reads from stdin (interactive mode)
//option -c executes the arguments that follow
int	main(int argc, char **argv, char **envp)
{
	rl_outstream = stderr;
	init_envp(envp);
	if (argc >= 2 && !ft_strcmp("-c", argv[1]))
		run_one_line(argc, argv);
	else
		minishell_loop();
	exit(g_ms.status);
}
