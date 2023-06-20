/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:03:44 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/20 18:38:57 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include <stdlib.h> //free

static void	set_io_num(t_token **tok, t_redir *redir)
{
	redir->io_num_used = false;
	if (tok_is(IO_NUMBER, *tok))
	{
		redir->io_num_used = true;
		redir->io_num = ft_atoi((*tok)->word);
		*tok = (*tok)->next;
	}
}

static void	set_dup2_params(t_token **tok, t_redir *redir)
{
	if (redir->type != REDIRECT_HEREDOC)
	{
		redir->filename = ft_strdup((*tok)->word);
		if (!redir->filename)
			print_error_and_exit("strdup failure");
	}
	*tok = (*tok)->next;
	if (redir->io_num_used)
		redir->target_fd = redir->io_num;
	else
	{
		if (redir->type == REDIRECT_IN || redir->type == REDIRECT_HEREDOC)
			redir->target_fd = STDIN_FILENO;
		else if (redir->type == REDIRECT_OUT || redir->type == REDIRECT_APPEND)
			redir->target_fd = STDOUT_FILENO;
	}
}

bool	parse_redirection(t_token **tok, t_ast *node, char **syntax_err)
{
	t_redir	*redir;

	redir = make_redir_struct();
	set_io_num(tok, redir);
	if (!tok_is(WORD, (*tok)->next))
	{
		set_syntax_error((*tok)->next, syntax_err);
		free(redir);
		return ;
	}
	redir->type = (*tok)->type;
	*tok = (*tok)->next;
	// if (redir->type == REDIRECT_HEREDOC)
	// 	read_heredoc();
	else
		set_dup2_params(tok, redir);
	add_redir_to_list(node, redir);
}
