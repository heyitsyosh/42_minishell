/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 20:15:53 by myoshika          #+#    #+#             */
/*   Updated: 2023/08/29 02:30:42 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../includes/ft_printf.h"
#include <readline/readline.h>
//readline, rl_on_new_line, rl_replace_line, rl_redisplay

//ctrl+\ (SIGQUIT), do nothing
//ctrl+c (SIGINT), prompt on new line
static void	signal_handler(int signum)
{
	g_ms.signum = signum;
}

static int	handle_sigint(void)
{
	if (g_ms.signum == SIGINT)
	{
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_ms.signum = 0;
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

void	setup_parent_signal_handler(void)
{
	g_ms.signum = 0;
	rl_event_hook = handle_sigint;
	if (signal(SIGINT, signal_handler) == SIG_ERR || \
		signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		print_error_and_exit("signal failure");
}
