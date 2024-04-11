/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 22:54:06 by myoshika          #+#    #+#             */
/*   Updated: 2024/04/12 04:19:02 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h> //STDOUT_FILENO
#include <stdlib.h> //EXIT_SUCCESS

int	builtin_pwd(t_token *args, t_data *d)
{
	(void)args;
	ft_putendl_fd(d->pwd, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
