/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_strjoin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 19:44:11 by myoshika          #+#    #+#             */
/*   Updated: 2023/09/05 03:32:29 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/get_next_line.h"
#include "../../../includes/minishell.h"

char	*x_strjoin_free(char *s1, char *s2, int to_free)
{
	char	*joined;

	joined = strjoin_free(s1, s2, to_free);
	if (!joined)
		print_error_and_exit("strjoin failure");
	return (joined);
}
