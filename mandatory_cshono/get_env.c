/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshono <cshono@student.42.tokyo>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 18:49:12 by cshono            #+#    #+#             */
/*   Updated: 2022/12/13 22:59:09 by cshono           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// size_t	ft_strlen(const char *s)
// {
// 	size_t	len;

// 	len = 0;
// 	while (*(s + len) != '\0')
// 		len++;
// 	return (len);
// }

// int	ft_strncmp(const char *s1, const char *s2, size_t n)
// {
// 	size_t				i;
// 	const unsigned char	*uc_s1 = (const unsigned char*)s1;
// 	const unsigned char	*uc_s2 = (const unsigned char*)s2;

// 	i = 0;
// 	if (n == 0)
// 		return (0);
// 	while (i < n && *(uc_s1 + i) && *(uc_s2 + i))
// 	{
// 		if (*(uc_s1 + i) != *(uc_s2 + i))
// 			break ;
// 		i++;
// 	}
// 	if (i == n)
// 		return (0);
// 	return (*(uc_s1 + i) - *(uc_s2 + i));
// }
	

t_env	*get_env(char *var, t_env *env)
{
	while (env->next != NULL)
	{
		if (!ft_strncmp(var,env->var,ft_strlen(var)))
			return (env);
		env = env->next;
	}
	return (env);
}
