/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 20:15:53 by myoshika          #+#    #+#             */
/*   Updated: 2023/09/07 20:30:51 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../includes/ft_printf.h"
#include <readline/readline.h>
//readline, rl_on_new_line, rl_replace_line, rl_redisplay
#include <signal.h> //signal, SIGINT, SIGQUIT, SIG_IGN, SIG_DFL, SIG_ERR

extern volatile sig_atomic_t	g_signum;

void	signal_handler(int signal)
{
	g_signum = signal;
}

static int	handle_sigint(void)
{
	if (g_signum == SIGINT)
	{
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_signum = 0;
	}
	return (0);
}

void	setup_child_signal_handler(void)
{
	rl_event_hook = NULL;
	if (signal(SIGINT, SIG_DFL) == SIG_ERR || \
		signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		print_error_and_exit("signal failure");
}

//ctrl+\ (SIGQUIT), do nothing
//ctrl+c (SIGINT), prompt on new line
void	setup_parent_signal_handler(void)
{
	g_signum = 0;
	rl_event_hook = handle_sigint;
	if (signal(SIGINT, signal_handler) == SIG_ERR || \
		signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		print_error_and_exit("signal failure");
}
