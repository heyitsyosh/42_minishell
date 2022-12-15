/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_m.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 23:27:12 by myoshika          #+#    #+#             */
/*   Updated: 2022/12/16 00:17:10 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_all_and_exit(t_minishell *m)
{
	if (m->line)
		free(m->line);
	if (m->old_pwd)
		free(m->old_pwd);
	if (m->pwd)
		free(m->pwd);
	// if (m->envp_head)
	// 	free
	// if (exit)
}

void	execute_line(t_minishell *m)
{
	tokenize(m->line, m);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	m;

	ft_bzero(&m, sizeof(t_minishell));
	init_envp(&m, envp);
	while (argc && argv)
	{
		set_signal_handlers();
		m.line = readline("minishell>");
		if (!m.line)
			break ;
			// return (exit_minishell(m));
		if (*m.line != '\0')
			add_history(m.line);
		execute_line(&m);
		ft_safe_free(m.line);
	}
	free_all_and_exit(&m);
}
