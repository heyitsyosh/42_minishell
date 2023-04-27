/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:26:06 by myoshika          #+#    #+#             */
/*   Updated: 2023/04/15 13:19:24 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h> //STDERR_FILENO
#include <stdlib.h> //getenv

volatile sig_atomic_t	g_status;

void	run_command(char *line)
{
	t_token		*tok;
	t_ast_node	*tree;

	tok = tokenize(line);
	tree = parser(&tok);
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
	free_ast(tree);
}

void	minishell_loop(void)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (*line)
		{
			add_history(line);
			run_command(line);
			free(line);
		}
	}
}

void	run_one_line(int argc, char **argv)
{
	if (argc == 2)
	{
		ft_putstr_fd("bash: -c: option requires an argument\n", STDERR_FILENO);
		exit(2);
	}
	if (ft_strlen(argv[2]) != 0)
		run_command(argv[2]);
}

int	main(int argc, char **argv)
{
	//rl_outstream = stderr;
	if (argc >= 2 && !ft_strcmp("-c", argv[1]))
		run_one_line(argc, argv);
	else
		minishell_loop();
	exit(g_status);
}
