/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 22:53:52 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/12 02:04:16 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/printf.h"
#include <stdlib.h> //EXIT_SUCCESS

int	builtin_env(t_token *args)
{
	t_env	*envp;

	(void)args;
	envp = g_ms.envp_head;
	while (envp)
	{
		ft_printf("%s=%s\n", envp->id, envp->str);
		envp = envp->next;
	}
	return (EXIT_SUCCESS);
}
