/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 06:09:18 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/14 00:58:16 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h> //free

void	run_commands(char *line)
{
	t_token		*tok;
	t_parse		*p;

	tok = tokenize(line);
	expand(tok);

	parser(&tok);
	/*
	if (!error)
	{
		set_up_redirect(node);
		execute(node);
		reset_redirect(node);
	}
	else
		set_exit_status
	*/
	// free(p);
	free_tokens(tok);
}
