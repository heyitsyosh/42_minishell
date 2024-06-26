/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 17:21:29 by myoshika          #+#    #+#             */
/*   Updated: 2024/04/12 05:42:39 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h> //INT_MAX
#include <stdlib.h> //free
#include <unistd.h> //write
#include "libft.h"
#include "ft_printf.h"

int	print_str(int fd, const char *input, size_t len)
{
	if (len < INT_MAX)
		write(fd, input, len);
	else
		len = INT_MAX;
	return (len);
}

int	no_conversion(const char *input, t_printf *info)
{
	char	*ptr_to_next_percent;
	size_t	len;
	int		print_len;

	ptr_to_next_percent = ft_strchr(input, '%');
	if (!ptr_to_next_percent)
		len = ft_strlen(input);
	else
		len = ptr_to_next_percent - input;
	print_len = print_str(info->fd, input, len);
	info->i += print_len;
	return (print_len);
}

int	put_str(t_printf *info, const char *str, bool need_to_free_str)
{
	size_t	s_len;
	int		printed;

	printed = 0;
	if (str == NULL)
	{
		need_to_free_str = true;
		str = ft_strdup("(null)");
		if (!str)
			return (INT_MAX);
	}
	s_len = ft_strlen(str);
	if (info->precision > -1 && (size_t)info->precision < s_len)
		s_len = info->precision;
	if (info->dash)
		printed += print_str(info->fd, str, s_len);
	if (info->width > -1)
		while ((size_t)info->width-- > s_len)
			printed += write(info->fd, &info->padding, 1);
	if (!info->dash)
		printed += print_str(info->fd, str, s_len);
	if (need_to_free_str)
		free((char *)str);
	return (printed);
}

int	put_char(t_printf *info, int chr)
{
	int		printed;

	printed = 0;
	if (info->dash)
		printed += write(info->fd, &chr, 1);
	while (info->width-- > 1)
		printed += write(info->fd, &info->padding, 1);
	if (!info->dash)
		printed += write(info->fd, &chr, 1);
	return (printed);
}
