/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 07:21:17 by myoshika          #+#    #+#             */
/*   Updated: 2023/09/04 22:27:18 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"
#include <stdlib.h> //malloc, free
#include <limits.h> //INT_MAX
#include <unistd.h> //STDOUT_FILENO

size_t	conversion(const char *specifiers, t_printf *info, va_list *args)
{
	int		printed;

	printed = 0;
	info->i += get_info(specifiers, info);
	if (info->width == INT_MAX || info->precision == INT_MAX
		|| !info->fmt || !ft_strchr("cspdiuxX%", info->fmt)
		|| (info->sharp && ft_strchr("xX", info->fmt)
			&& info->precision >= INT_MAX - 2))
		return (INT_MAX);
	if (info->fmt == 'c')
		printed += put_char(info, va_arg(*args, int));
	else if (info->fmt == 's')
		printed += put_str(info, va_arg(*args, char *), false);
	else if (info->fmt == 'p')
		printed += put_unsigned(info, va_arg(*args, unsigned long long));
	else if (info->fmt == 'd' || info->fmt == 'i')
		printed += put_signed(info, ft_itoa(va_arg(*args, int)));
	else if (ft_strchr("uxX", info->fmt))
		printed += put_unsigned(info, va_arg(*args, unsigned int));
	else if (info->fmt == '%')
		printed += put_char(info, '%');
	return (printed);
}

static void	init(t_printf *info)
{
	info->fmt = ' ';
	info->precision = -1;
	info->width = -1;
	info->dash = false;
	info->padding = ' ';
	info->sharp = false;
	info->sign = '\0';
}

int	ft_dprintf(int fd, const char *input, ...)
{
	va_list		args;
	t_printf	info;
	size_t		printed;

	printed = 0;
	info.i = 0;
	info.fd = fd;
	va_start(args, input);
	while (printed < INT_MAX && input[info.i])
	{
		init(&info);
		if (input[info.i] == '%')
			printed += conversion(input + (++info.i), &info, &args);
		else
			printed += no_conversion(input + info.i, &info);
	}
	va_end(args);
	if (printed >= INT_MAX)
		return (-1);
	return (printed);
}

int	ft_printf(const char *input, ...)
{
	va_list		args;
	t_printf	info;
	size_t		printed;

	printed = 0;
	info.i = 0;
	info.fd = STDOUT_FILENO;
	va_start(args, input);
	while (printed < INT_MAX && input[info.i])
	{
		init(&info);
		if (input[info.i] == '%')
			printed += conversion(input + (++info.i), &info, &args);
		else
			printed += no_conversion(input + info.i, &info);
	}
	va_end(args);
	if (printed >= INT_MAX)
		return (-1);
	return (printed);
}
