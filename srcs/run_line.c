/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 06:09:18 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/20 17:00:06 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h> //free

void	run_line(char *line)
{
	t_token	*tok;
	t_ast	*ast;

	tok = tokenize(line);
	expand(tok);
	ast = parser(tok);
	free_tokens(tok);
	if (ast)
		execute(make_exec_struct(), ast);
	else
		g_ms.exit_status = 2;
	free_ast(ast);
}
