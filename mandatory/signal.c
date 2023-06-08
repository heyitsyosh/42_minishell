/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 20:15:53 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/09 01:53:24 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//ctrl+\ (SIGQUIT), do nothing
//ctrl+c (SIGINT), prompt on new line
void	signal_handler(int signum)
{
	ft_printf("\n");
	rl_on_new_line();
}

//SIGDFL in child proccess, dont want to kill the parent signal
void	setup_child_signal_handler(void)
{
	if (signal(SIGINT, SIG_DFL) == SIG_ERR \
		|| signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		print_error_and_exit("signal failure");
}

void	setup_parent_signal_handler(void)
{
	if (signal(SIGINT, signal_handler) == SIG_ERR \
		|| signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		print_error_and_exit("signal failure");
}

//signal to-do: 
//test [usami san's examples (esp understand heredoc)]
//figure out how to display the ctrl+d message
//write signal handler