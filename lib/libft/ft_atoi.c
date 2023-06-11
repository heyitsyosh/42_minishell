/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 23:20:06 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/11 19:25:32 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include <limits.h> //LONG_MAX, LONG_MIN
#include <errno.h> //errno, ERANGE

static long	make_l(const char *str, size_t i, int sign, long num)
{
	long	min;

	min = LONG_MIN;
	while (*(str + i) && (*(str + i) >= '0' && *(str + i) <= '9'))
	{
		if (sign == 1 && ((num > LONG_MAX / 10)
				|| (num == LONG_MAX / 10 && *(str + i) - '0' > LONG_MAX % 10)))
		{
			errno = ERANGE;
			return (LONG_MAX);
		}
		else if (sign == -1 && ((num < min / 10)
				|| (num == min / 10 && *(str + i) - '0' > min % 10 * -1)))
		{
			errno = ERANGE;
			return (LONG_MIN);
		}
		num = (num * 10) + sign * (*(str + i) - '0');
		i++;
	}
	return (num);
}

int	ft_atoi(const char *str)
{
	size_t	i;
	long	num;
	int		sign;

	i = 0;
	sign = 1;
	while (ft_isspace(*(str + i)))
		i++;
	if ((*(str + i) == '+' || *(str + i) == '-') && *(str + i))
	{
		if (*(str + i) == '-')
			sign = -1;
		i++;
	}
	num = make_l(str, i, sign, 0);
	return ((int)num);
}
