/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:26:06 by myoshika          #+#    #+#             */
/*   Updated: 2024/04/12 05:09:36 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_printf.h"
#include "libft.h"
#include <readline/readline.h> //readline
#include <readline/history.h> //add_history
#include <unistd.h> //STDERR_FILENO
#include <stdlib.h> //exit, free

volatile sig_atomic_t	g_signum;

static void	run_line(char *line, t_data *d)
{
	t_token	*tok;
	t_ast	*ast;

	tok = tokenize(line);
	if (!tok)
		return ;
	add_history(line);
	expand(tok, d);
	ast = parser(tok);
	free_tokens(tok);
	d->fork_failed = 0;
	if (ast)
		execute(ast, d);
	else
		d->exit_status = 2;
	free_ast(ast);
}

static void	run_repl(t_data *d)
{
	char	*line;

	while (1)
	{
		setup_parent_signal_handler();
		line = readline("minishell> ");
		if (g_signum == SIGINT)
		{
			d->exit_status = 130;
			g_signum = 0;
		}
		if (!line)
			break ;
		if (*line)
			run_line(line, d);
		free(line);
	}
	ft_printf("\n");
}

static void	run_one_line(int argc, char **argv, t_data *d)
{
	if (argc == 2)
	{
		ft_dprintf(STDERR_FILENO, "bash: -c: option requires an argument\n");
		exit(2);
	}
	if (ft_strlen(argv[2]) != 0)
		run_line(argv[2], d);
}

//default execution reads from stdin (interactive mode)
//option -c executes the arguments that follow
int	main(int argc, char **argv, char **envp)
{
	t_data	d;

	rl_outstream = stderr;
	init_envp(envp, &d);
	d.exit_status = 0;
	if (argc >= 2 && !ft_strcmp("-c", argv[1]))
		run_one_line(argc, argv, &d);
	else
		run_repl(&d);
	exit(d.exit_status);
}
