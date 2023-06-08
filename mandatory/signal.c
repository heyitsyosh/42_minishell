/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 20:15:53 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/09 05:35:49 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//ctrl+\ (SIGQUIT), do nothing
//ctrl+c (SIGINT), prompt on new line
void	signal_handler(int signum)
{
	g_ms.signum = signum;
	if (g_ms.signum == SIGINT)
		g_ms.status = 130;
}

void	setup_child_signal_handler(void)
{
	if (signal(SIGINT, SIG_DFL) == SIG_ERR \
		|| signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		print_error_and_exit("signal failure");
}

void	setup_parent_signal_handler(void)
{
	g_ms.signum = 0;
	if (signal(SIGINT, signal_handler) == SIG_ERR \
		|| signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		print_error_and_exit("signal failure");
}
