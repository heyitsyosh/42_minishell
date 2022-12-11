/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_m.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 23:27:12 by myoshika          #+#    #+#             */
/*   Updated: 2022/12/11 21:30:07 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



// execute_line()
// {
	
// }

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	//t_minishell	m;

	int i = 0;
	while(*(envp + i))
	{
		printf("[%d]%s\n", i, *(envp + i));
		i++;
	}
	while (argc && argv)
	{
		//signal_handling();
		line = readline("minishell>");
		if (!line)
			break ;
			// return (exit_minishell(m));
		if (*line != '\0')
			add_history(line);
		//execute_line();
		free(line);
	}
	//exit();
}
