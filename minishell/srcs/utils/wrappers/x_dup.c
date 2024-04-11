/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_dup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 22:02:21 by myoshika          #+#    #+#             */
/*   Updated: 2024/04/12 04:16:10 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h> //dup

int	x_dup(int oldfd)
{
	int	fd;

	fd = dup(oldfd);
	if (fd == -1)
		print_error_and_exit("dup failure");
	return (fd);
}
