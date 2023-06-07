/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 20:15:53 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/07 23:42:37 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//ctrl+\ (SIGQUIT), ctrl+c (SIGINT)
void	signal_handler(void)
{
	if (signal(SIGINT, SIG_IGN) == SIG_ERR \
		|| signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		print_error_and_exit("signal failure");
}
