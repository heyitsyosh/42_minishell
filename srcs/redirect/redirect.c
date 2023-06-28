/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 20:41:33 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/25 18:34:27 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft.h"
#include <fcntl.h> //O_*
#include <unistd.h> //open, close, dup, dup2, STDERR_FILENO

//dup2(oldfd, newfd, ...)
//dup2(filefd, target_fd)

static bool	open(t_redir *r)
{
	if (r->type == RD_OUT)
		r->file_fd = open(r->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (r->type == RD_IN)
		r->file_fd = open(r->filename, O_RDONLY);
	else if (r->type == RD_APPEND)
		r->file_fd = open(r->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (r->file_fd == -1)
	{
		msg_to_stderr(r->filename, ": ", strerror(errno));
		ft_putstr_fd("'\n", STDERR_FILENO);
		return (false);
	}
	return (true);
}

bool	open_redir_files(t_redir *redir)
{
	while (redir)
	{
		if (redir->io_num > 1048575)
			msg_to_stderr(ft_itoa(redir->io_num), ": ", "Bad file descriptor\n");
		if (redir->io_num > 1048575 || !open(redir))
		{
			g_ms.exit_status = 1;
			return (false);
		}
		redir = redir->next;
	}
	return (true);
}

//bad file descriptor from ulimit -n
void	set_up_redirect(t_redir *redir)
{
	if (!redir)
		return ;
	redir->stashed_target_fd = dup(target_fd);
	if ()
	do_redirect();
}


void	reset_redirect(t_redir *redir)
{
	if (!redir)
		return ;
	while (redir)
	{
		if (close(redir->file_fd) == -1 \
			|| close(redir->target_fd) == -1)
			print_error_and_exit("close failure");
		if (dup2(stashed_target_fd, target_fd) == -1)
			print_error_and_exit("dup2 failure");
		redir = redir->next;
	}
}
