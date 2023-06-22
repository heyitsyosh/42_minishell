/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:03:44 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/21 22:14:34 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include <stdlib.h> //free
#include <unistd.h> //STDIN_FILENO, STDERR_FILENO

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

static void	set_redir_info(t_token **tok, t_redir *redir)
{
	char	*str_after_redir;

	str_after_redir = ft_strdup((*tok)->word);
	if (!str_after_redir)
		print_error_and_exit("strdup failure");
	if (redir->type == RD_HEREDOC)
		redir->delimitor = str_after_redir;
	else
		redir->filename = str_after_redir;
	*tok = (*tok)->next;
	if (redir->io_num_used)
		redir->target_fd = redir->io_num;
	else
	{
		if (redir->type == RD_IN || redir->type == RD_HEREDOC)
			redir->target_fd = STDIN_FILENO;
		else if (redir->type == RD_OUT || redir->type == RD_APPEND)
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
	set_redir_info(tok, redir);
	add_redir_to_list(node, redir);
}
