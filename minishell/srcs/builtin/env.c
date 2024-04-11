/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 22:53:52 by myoshika          #+#    #+#             */
/*   Updated: 2024/04/12 04:19:19 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_printf.h"
#include <stdlib.h> //EXIT_SUCCESS

int	builtin_env(t_token *args, t_data *d)
{
	t_env	*envp;

	(void)args;
	envp = d->envp;
	while (envp)
	{
		ft_printf("%s=%s\n", envp->id, envp->str);
		envp = envp->next;
	}
	return (EXIT_SUCCESS);
}
