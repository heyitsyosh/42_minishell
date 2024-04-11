/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_close.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 02:19:33 by myoshika          #+#    #+#             */
/*   Updated: 2024/04/12 04:16:05 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h> //close

int	x_close(int fd)
{
	if (close(fd) == -1)
		print_error_and_exit("close failure");
	return (0);
}
