/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_m.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 23:27:12 by myoshika          #+#    #+#             */
/*   Updated: 2022/12/12 00:28:01 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// execute_line(char *line, )
// {
	
// }

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_minishell	m;

	init_shell(&m, envp);
	while (argc && argv)
	{
		//set_signal();
		line = readline("minishell>");
		if (!line)
			break ;
			// return (exit_minishell(m));
		if (*line != '\0')
			add_history(line);
		//execute_line(line, &m);
		free(line);
	}
	//exit();
}

/*
SHLVL 設定
PWD/OLDPWDを設定するいみを調べる

env
unset/export機能

lexer：lineを分ける

list vs char **
*/