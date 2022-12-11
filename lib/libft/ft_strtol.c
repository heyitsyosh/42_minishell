/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 00:41:53 by myoshika          #+#    #+#             */
/*   Updated: 2022/12/12 01:05:35 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static long	make_l(const char *str, size_t *i, int sign, long num)
{
	long	min;

	min = LONG_MIN;
	while (str[*i] && (str[*i] >= '0' && str[*i] <= '9'))
	{
		if (sign == 1 && ((num > LONG_MAX / 10)
				|| (num == LONG_MAX / 10 && str[*i] - '0' > LONG_MAX % 10)))
		{
			errno = ERANGE;
			return (LONG_MAX);
		}
		else if (sign == -1 && ((num < min / 10)
				|| (num == min / 10 && str[*i] - '0' > min % 10 * -1)))
		{
			errno = ERANGE;
			return (LONG_MIN);
		}
		num = (num * 10) + sign * (str[*i] - '0');
		(*i)++;
	}
	return (num);
}


static	skip_before_num()
{
	while (nptr[i] == 32 || (9 <= nptr[i] && nptr[i] <= 13))
		i++;
	if ((nptr[i] == '+' || nptr[i] == '-') && nptr[i])
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
}

long	strtol(const char *nptr, char **endptr, int base)
{
	size_t	i;
	int		sign;
	long	num;

	sign = 1;
	i = 0;
	i += skip_before_num(nptr, base)
	num = make_l(nptr, &i, sign, 0);
	*endptr = nptr + i;
	if (!nptr[i])
		*endptr = NULL;
	return (num);
}
