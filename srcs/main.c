/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:26:06 by myoshika          #+#    #+#             */
/*   Updated: 2023/08/31 21:11:14 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/ft_printf.h"
#include "../includes/libft.h"
#include <readline/readline.h> //readline
#include <readline/history.h> //add_history
#include <unistd.h> //STDERR_FILENO
#include <stdlib.h> //exit, free

t_minishell	g_ms;

static void	run_line(char *line)
{
	t_token	*tok;
	t_ast	*ast;

	tok = tokenize(line);
	if (tok)
		add_history(line);
	expand(tok);
	ast = parser(tok);
	free_tokens(tok);
	if (ast)
		execute(ast);
	else
		g_ms.exit_status = 2;
	free_ast(ast);
}

static void	minishell_loop(void)
{
	char	*line;

	while (1)
	{
		setup_parent_signal_handler();
		line = readline("minishell> ");
		if (!line)
			break ;
		if (*line)
		{
			run_line(line);
			free(line);
		}
	}
	ft_printf("exit\n");
}

static void	run_one_line(int argc, char **argv)
{
	if (argc == 2)
	{
		ft_putstr_fd("bash: -c: option requires an argument\n", STDERR_FILENO);
		exit(2);
	}
	if (ft_strlen(argv[2]) != 0)
		run_line(argv[2]);
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
	exit(g_ms.exit_status);
}
