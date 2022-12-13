/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshono <cshono@student.42.tokyo>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 01:33:26 by cshono            #+#    #+#             */
/*   Updated: 2022/12/12 19:06:57 by cshono           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_env *ft_unset(char *str, t_env *env)
{
	int	i;

	i = 0;
	while (env->next != '\0')
	{
		if (env->string == str)
	}
	while (str != env->string)
	{
		env = env->next

	}
	env = env->prev;

}