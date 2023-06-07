/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 22:53:52 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/08 00:09:51 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libft.h"

int	builtin_env(t_token *args, t_minishell *m)
{
	t_env	*envp;

	(void)args;
	envp = m->envp_head;
	while (envp)
	{
		ft_printf("%s=%s\n", envp->id, envp->str);
		envp = envp->next;
	}
	return (EXIT_SUCCESS);
}
