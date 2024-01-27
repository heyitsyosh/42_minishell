/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 16:46:50 by myoshika          #+#    #+#             */
/*   Updated: 2023/09/04 22:27:02 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "./libft.h"
# include <stdbool.h> //bool
# include <stddef.h> //size_t
# include <stdarg.h> //va_start, va_end, va_arg, va_list

typedef struct s_printf
{
	size_t	i;
	int		fd;
	char	fmt;	
	int		precision;
	int		width;
	bool	dash;
	char	padding;
	bool	sharp;
	char	sign;
}	t_printf;

int		ft_printf(const char *input, ...);
int		ft_dprintf(int fd, const char *input, ...);

size_t	get_info(const char *after_pct, t_printf *info);

int		put_char(t_printf *info, int chr);
int		put_str(t_printf *info, const char *str, bool need_to_free_str);
int		put_unsigned(t_printf *info, unsigned long long ull);
int		put_signed(t_printf *info, char *num);
int		put_num(char *num, int num_len, int printed, t_printf *info);

int		no_conversion(const char *input, t_printf *info);

char	*ft_ulltoa(unsigned long long ull, int base, t_printf *info);
int		print_str(int fd, const char *input, size_t len);
#endif
