/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:03:44 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/20 02:43:45 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include <stdlib.h> //malloc, free

static t_redirect	*make_redir_struct(void)
{
	t_redirect	*redir;

	redir = (t_redirect *)malloc(sizeof(t_redirect));
	if (!redir)
		print_error_and_exit("malloc failure");
	redir->filename == NULL;
	redir->prev = NULL;
	redir->next = NULL;
	return (redir);
}

static void	set_io_num(t_token **tok, t_redirect *redir)
{
	redir->io_num_used = false;
	if (tok_is(IO_NUMBER, *tok))
	{
		redir->io_num_used = true;
		redir->io_num = ft_atoi((*tok)->word);
		//error?
		*tok = (*tok)->next;
	}
}

static void	set_dup_params(t_token **tok, t_redir *redir)
{
	redir->filename = ft_strdup((*tok)->word);
	if (!redir->filename)
		print_error_and_exit("strdup failure");
	*tok = (*tok)->next;
	if (redir->type == REDIRECT_IN)
		redir->targetfd = STDIN_FILENO;
	else if (redir->type == REDIRECT_OUT || redir->type == REDIRECT_APPEND)
		redir->targetfd = STDOUT_FILENO;
	if (io_num_used)
		redir->targetfd = redir->io_num;
}

void	parse_redirection(t_token **tok, t_ast *node, char **syntax_err)
{
	t_redir	*redir;

	redir = make_redir_struct();
	set_io_num(tok, node);
	if (!tok_is(WORD, (*tok)->next))
	{
		set_syntax_error((*tok)->next, syntax_err);
		free(redir);
		return ;
	}
	redir->type = (*tok)->type;
	*tok = (*tok)->next;
	// if (redir->type == REDIRECT_HEREDOC)
		
	else
		set_dup_params(tok, redir);
}

//1>4>5
//1> 4 > 5
//> 4 > 5

//dup2(oldfd, newfd, ...)
//dup2(filefd, target_fd)

// Redirecting output example
//command          : "1 > out"
// targetfd         : 1
// filename         : "out"
// filefd           : open("out")
// stashed_targetfd : dup(targetfd)