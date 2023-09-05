/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_fork.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 19:44:11 by myoshika          #+#    #+#             */
/*   Updated: 2023/09/05 22:22:50 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include <unistd.h> //fork

pid_t	x_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		print_error_and_exit("fork failure");
	return (pid);
}
