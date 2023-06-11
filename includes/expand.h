/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 22:23:03 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/11 22:02:56 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

typedef enum e_sub_word_type
{
	QUOTED,
	DQUOTED,
	UNQUOTED,
	WILDCARD,
	HEAD,
}	t_sub_word_type;

typedef struct s_word
{
	char			*sub_word;
	t_sub_word_type	type;
	struct s_word	*next;
}	t_word;

#endif