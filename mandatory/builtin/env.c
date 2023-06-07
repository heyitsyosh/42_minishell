/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 22:53:52 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/07 23:51:47 by myoshika         ###   ########.fr       */
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
		ft_printf("%s=%s", envp->id, envp->str);
		if (print_nl)
			ft_printf("\n");
		envp = envp->next;
	}
	return (EXIT_SUCCESS);
}
