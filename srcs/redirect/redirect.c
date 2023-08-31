/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 20:41:33 by myoshika          #+#    #+#             */
/*   Updated: 2023/08/31 22:02:13 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include <errno.h> //errno
#include <string.h> //strerror
#include <fcntl.h> //O_*
#include <unistd.h> //open, dup, STDERR_FILENO

static bool	open_fd(t_redir *r, bool process_type)
{
	g_ms.heredoc_interrupted = false;
	if (r->type == RD_OUT)
		r->file_fd = open(r->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (r->type == RD_IN)
		r->file_fd = open(r->filename, O_RDONLY);
	else if (r->type == RD_APPEND)
		r->file_fd = open(r->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (r->type == RD_HEREDOC)
	{
		r->file_fd = set_up_heredoc(r);
		if (process_type == IS_CHILD)
			setup_child_signal_handler();
		else
			setup_parent_signal_handler();
	}
	if (r->file_fd == -1)
	{
		if (!g_ms.heredoc_interrupted)
		{
			msg_to_stderr(r->filename, ": ", strerror(errno));
			ft_putstr_fd("\n", STDERR_FILENO);
		}
		return (false);
	}
	return (true);
}

//bad file descriptor range from ulimit -n
bool	open_redir_files(t_redir *redir, bool process_type)
{
	while (redir)
	{
		if (redir->io_num > 1048575)
			msg_to_stderr(ft_itoa(redir->io_num), ": ", "Bad file descriptor\n");
		if (!open_fd(redir, process_type) || (redir->io_num > 1048575))
		{
			g_ms.exit_status = 1;
			while (redir->prev)
			{
				x_close(redir->prev->file_fd);
				redir = redir->prev;
			}
			return (false);
		}
		redir = redir->next;
	}
	return (true);
}

void	set_up_redirect(t_redir *redir)
{
	if (!redir)
		return ;
	while (redir)
	{
		redir->stashed_target_fd = x_dup(redir->target_fd);
		x_dup2(redir->file_fd, redir->target_fd);
		redir = redir->next;
	}
}

void	reset_redirect(t_redir *redir)
{
	if (!redir)
		return ;
	while (redir)
	{
		x_close(redir->file_fd);
		x_close(redir->target_fd);
		x_dup2(redir->stashed_target_fd, redir->target_fd);
		redir = redir->prev;
	}
}
