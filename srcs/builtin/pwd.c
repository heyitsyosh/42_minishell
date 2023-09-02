/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 22:54:06 by myoshika          #+#    #+#             */
/*   Updated: 2023/09/03 04:02:04 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include <unistd.h> //STDERR_FILENO
#include <stdlib.h> //EXIT_SUCCESS

int	builtin_pwd(t_token *args, t_data *d)
{
	(void)args;
	ft_putendl_fd(d->pwd, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
