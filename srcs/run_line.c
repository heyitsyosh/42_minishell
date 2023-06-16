/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 06:09:18 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/16 23:38:45 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h> //free

void	run_line(char *line)
{
	t_token		*tok;
	t_ast_node	*ast;

	tok = tokenize(line);
	expand(tok);
	ast = parser(&tok);
	/*
	if (ast)
	{
		set_up_redirect(node);
		execute(node);
		reset_redirect(node);
	}
	else
		g_ms.exit_status = 2;
	*/
	free_ast(ast);
	free_tokens(tok);
}
