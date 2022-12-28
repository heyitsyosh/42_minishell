/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 23:27:12 by myoshika          #+#    #+#             */
/*   Updated: 2022/12/27 02:38:34 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_line(t_minishell *m)
{
	builtin_env(m);
	fflush(stdout);
	tokenize(m->line, m);
	// expand();
	print_tokens(m);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	m;

	ft_bzero(&m, sizeof(t_minishell));
	init_envp(envp, &m);
	while (argc && argv)
	{
		//  set_signal_handlers();
		m.line = readline("minishell>");
		if (!m.line)
			exit(EXIT_FAILURE);
		if (*m.line != '\0')
			add_history(m.line);
		execute_line(&m);
		ft_safe_free(&m.line);
		free_tokens(m.token_head);
		printf("wth");
		fflush(stdout);
	}
}
