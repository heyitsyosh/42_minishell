/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 23:27:12 by myoshika          #+#    #+#             */
/*   Updated: 2022/12/19 19:29:03 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_line(t_minishell *m)
{
	tokenize(m->line, m);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	m;

	ft_bzero(&m, sizeof(t_minishell));
	init_envp(envp, &m);
	while (argc && argv)
	{
		set_signal_handlers();
		m.line = readline("minishell>");
		if (!m.line)
			exit(EXIT_FAILURE);
		if (*m.line != '\0')
			add_history(m.line);
		execute_line(&m);
		ft_safe_free(m.line);
		free_tokens(m.token_head);
	}
}
