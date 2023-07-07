/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_strdup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 19:44:11 by myoshika          #+#    #+#             */
/*   Updated: 2023/07/03 19:44:15 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libft.h"

char	*x_strdup(const char *to_dup)
{
	char	*dup;

	dup = ft_strdup(to_dup);
	if (!to_dup)
		print_error_and_exit("strdup failure");
	return (dup);
}
