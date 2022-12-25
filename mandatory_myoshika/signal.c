/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 03:42:20 by myoshika          #+#    #+#             */
/*   Updated: 2022/12/19 19:29:24 by myoshika         ###   ########.fr       */
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
		exit(EXIT_FAILURE);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		exit(EXIT_FAILURE);
}
