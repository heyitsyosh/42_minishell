/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 20:41:33 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/25 17:28:14 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft.h"
#include <fcntl.h> //O_*
#include <unistd.h> //open, close, STDERR_FILENO

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
		if (!open(redir))
		{
			//error message?
			return (false);
		}
		redir = redir->next;
	}
	return (true);
}

//dup2(oldfd, newfd, ...)
//dup2(filefd, target_fd)

void	stash_file()
{
	
}

void	do_redirect()
{
	
}

//bad file descriptor from ulimit -n
//if (redir->io_num > 1048575)
void	set_up_redirect(t_redir *redir)
{
	if (!redir)
		return ;
	stash_file();
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
