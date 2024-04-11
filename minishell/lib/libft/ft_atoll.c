/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 00:44:54 by myoshika          #+#    #+#             */
/*   Updated: 2024/04/12 04:07:40 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h> //LLONG_MAX, LLONG_MIN
#include <errno.h> //errno, ERANGE
#include "libft.h"

static long	make_ll(const char *str, size_t i, int sign, long num)
{
	long long	min;
	long long	max;

	min = LLONG_MIN;
	max = LLONG_MAX;
	while (*(str + i) && (*(str + i) >= '0' && *(str + i) <= '9'))
	{
		if (sign == 1 && ((num > max / 10)
				|| (num == max / 10 && *(str + i) - '0' > max % 10)))
		{
			errno = ERANGE;
			return (LLONG_MAX);
		}
		else if (sign == -1 && ((num < min / 10)
				|| (num == min / 10 && *(str + i) - '0' > min % 10 * -1)))
		{
			errno = ERANGE;
			return (LLONG_MIN);
		}
		num = (num * 10) + sign * (*(str + i) - '0');
		i++;
	}
	return (num);
}

long long	ft_atoll(const char *str)
{
	size_t		i;
	long long	num;
	int			sign;

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
	num = make_ll(str, i, sign, 0);
	return (num);
}
