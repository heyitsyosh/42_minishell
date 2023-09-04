/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 20:41:33 by myoshika          #+#    #+#             */
/*   Updated: 2023/09/04 22:24:48 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/ft_printf.h"
#include "../../includes/libft.h"
#include <errno.h> //errno
#include <string.h> //strerror
#include <fcntl.h> //O_*
#include <unistd.h> //open, dup, STDERR_FILENO

extern volatile sig_atomic_t	g_signum;

static bool	open_fd(t_redir *r, bool process_type, t_data *d)
{
	if (r->type == RD_OUT)
		r->file_fd = open(r->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (r->type == RD_IN)
		r->file_fd = open(r->filename, O_RDONLY);
	else if (r->type == RD_APPEND)
		r->file_fd = open(r->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (r->type == RD_HEREDOC)
	{
		r->file_fd = set_up_heredoc(r, d);
		g_signum = 0;
		if (process_type == IS_CHILD)
			setup_child_signal_handler();
		else
			setup_parent_signal_handler();
		if (r->file_fd == -1)
			return (false);
	}
	if (r->file_fd == -1)
	{
		ft_dprintf(STDERR_FILENO, "%s: %s\n", r->filename, strerror(errno));
		return (false);
	}
	return (true);
}

//bad file descriptor range from ulimit -n
bool	open_redir_files(t_redir *redir, bool process_type, t_data *d)
{
	while (redir)
	{
		if (redir->io_num > 1048575)
			ft_dprintf(STDERR_FILENO, \
			"%d: %s\n", redir->io_num, "Bad file descriptor");
		if (!open_fd(redir, process_type, d) || (redir->io_num > 1048575))
		{
			d->exit_status = 1;
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
	while (redir->next)
		redir = redir->next;
	while (redir)
	{
		x_close(redir->file_fd);
		x_close(redir->target_fd);
		x_dup2(redir->stashed_target_fd, redir->target_fd);
		redir = redir->prev;
	}
}
