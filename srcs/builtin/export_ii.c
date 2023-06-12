/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_ii.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 02:05:54 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/13 05:29:05 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/ft_printf.h"

void	export_no_args(void)
{
	t_env	*envp;

	envp = g_ms.envp_head;
	while (envp)
	{
		ft_printf("declare -x %s=\"%s\"\n", envp->id, envp->str);
		envp = envp->next;
	}
}
