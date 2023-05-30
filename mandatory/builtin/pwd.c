/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 22:54:06 by myoshika          #+#    #+#             */
/*   Updated: 2023/05/30 23:32:31 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libft.h"

int	builtin_pwd(t_token *args, t_minishell *m)
{
	(void)args;
	ft_putendl_fd(m.pwd, STDOUT_FILENO);
	return (EXIT_SUCESS);
}
