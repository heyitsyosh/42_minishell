/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 23:20:16 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/11 19:20:01 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include <stdlib.h> //malloc

void	*ft_calloc(size_t count, size_t size)
{
	void	*ret;

	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	if ((size_t) - 1 / count < size)
		return (NULL);
	ret = malloc(size * count);
	if (ret != NULL)
		ft_bzero(ret, size * count);
	return (ret);
}
