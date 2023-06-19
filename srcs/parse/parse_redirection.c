/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:03:44 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/19 18:33:05 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include <stdlib.h> //malloc

static t_redirect	*make_redir_struct(void)
{
	t_redirect	*redir;

	redir = (t_redirect *)malloc(sizeof(t_redirect));
	if (!redir)
		print_error_and_exit("malloc failure");
	//
	return (redir);
}

void	parse_redirection(t_token **tok, t_ast *node, char **syntax_err)
{
	if (!node->redir)
		make_redir_struct();
	if ((*tok)->type == IO_NUMBER)
		
	if ((*tok))
	{
		set_syntax_error((*tok)->next, syntax_err)
		return ;
	}
}

//1>4>5
//1> 4 > 5
//> 4 > 5