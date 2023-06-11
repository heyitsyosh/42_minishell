/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_safe_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 05:04:18 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/11 19:22:38 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include <stdlib.h> //free

void	ft_safe_free(char **pointer)
{
	if (*pointer)
	{
		free(*pointer);
		*pointer = NULL;
	}
}
