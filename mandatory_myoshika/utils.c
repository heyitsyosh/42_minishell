/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 21:13:21 by myoshika          #+#    #+#             */
/*   Updated: 2022/12/16 22:01:48 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_tokens(t_token *token)
{
	while (token)
	{
		free(token->token);
		if (token->cmd)
		{
			free((token->cmd)->command);
			free((token->cmd)->exec_path);
			free(token->cmd);
		}
		token = token->next;
	}
}
