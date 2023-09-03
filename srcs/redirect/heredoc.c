/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 20:30:10 by myoshika          #+#    #+#             */
/*   Updated: 2023/09/03 20:49:29 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"
#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include <readline/readline.h> //readline, rl_done
#include <unistd.h> //write
#include <stdlib.h> //free
#include <sys/types.h>
#include <sys/stat.h> //O_*
#include <fcntl.h> //open

extern volatile sig_atomic_t	signum;

static int	handle_heredoc_sigint(void)
{
	if (signum == SIGINT)
		rl_done = 1;
	return (0);
}

static void	setup_heredoc_signal_handler(void)
{
	signum = 0;
	if (signal(SIGINT, signal_handler) == SIG_ERR || \
		signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		print_error_and_exit("signal failure");
	rl_event_hook = handle_heredoc_sigint;
}

static void	readline_heredoc_loop(int fd, char *delimiter)
{
	char	*buf;

	while (1)
	{
		buf = readline("> ");
		if (!buf || ft_strcmp(buf, delimiter) == 0 || signum == SIGINT)
		{
			free(buf);
			break ;
		}
		buf = ft_strjoin_with_free(buf, "\n", FREE_FIRST_PARAM);
		if (!buf)
			print_error_and_exit("strjoin failure");
		write(fd, buf, ft_strlen(buf));
		free(buf);
	}
}

static int	delete_tmp_file(int fd, char *fd_name)
{
	close(fd);
	fd = open(fd_name, O_RDONLY);
	if (fd == -1)
		print_error_and_exit("open failure");
	if (unlink(fd_name) == -1)
		print_error_and_exit("unlink failure");
	free(fd_name);
	return (fd);
}

int	set_up_heredoc(t_redir *redir, t_data *d)
{
	int		fd;
	char	*fd_name;

	fd_name = ft_strjoin_with_free("./objs/", d->shlvl, FREE_NONE);
	fd = open(fd_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		print_error_and_exit("open failure");
	setup_heredoc_signal_handler();
	readline_heredoc_loop(fd, redir->delimiter);
	fd = delete_tmp_file(fd, fd_name);
	if (signum == SIGINT)
	{
		d->exit_status = 1;
		x_close(fd);
		return (-1);
	}
	return (fd);
}
