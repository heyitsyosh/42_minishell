/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshono <cshono@student.42.tokyo>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 17:01:33 by cshono            #+#    #+#             */
/*   Updated: 2022/12/25 17:08:54 by cshono           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_env(t_minishell *m)
{
	t_env	*env;

	env = m->envp_head;
	while (env != NULL)
	{
		printf("%s=%s\n",env->id,env->str);
		env = env->next;
	}
}