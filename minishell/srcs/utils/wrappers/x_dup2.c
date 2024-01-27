/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_dup2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 02:19:35 by myoshika          #+#    #+#             */
/*   Updated: 2023/08/30 02:23:14 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include <unistd.h> //dup2

int	x_dup2(int oldfd, int newfd)
{
	int	fd;

	fd = dup2(oldfd, newfd);
	if (fd == -1)
		print_error_and_exit("dup2 failure");
	return (fd);
}
