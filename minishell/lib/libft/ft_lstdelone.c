/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 23:28:37 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/11 19:21:05 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include <stdlib.h> //free

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!(lst == NULL || del == NULL))
		del(lst->content);
	free(lst);
}
