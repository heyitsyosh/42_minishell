/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 03:42:20 by myoshika          #+#    #+#             */
/*   Updated: 2022/12/12 03:51:26 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <signal.h>

static void	handler(int signal)
{
	//interrupt! go back to previous state (don't apply any changes unless command already fulfilled)
	//delete line, show prompt, handle so no leaks
}

void	set_signal_handlers(void)
{
	if (signal(SIGINT, &handler) == SIG_ERR)
		exit (1);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		exit (1);
}
