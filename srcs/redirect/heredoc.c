/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 20:30:10 by myoshika          #+#    #+#             */
/*   Updated: 2023/09/04 04:48:49 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"
#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include <readline/readline.h> //readline, rl_done
#include <unistd.h> //write, pipe, close
#include <stdlib.h> //free

extern volatile sig_atomic_t	g_signum;

static int	handle_heredoc_sigint(void)
{
	if (g_signum == SIGINT)
		rl_done = 1;
	return (0);
}

static void	setup_heredoc_signal_handler(void)
{
	g_signum = 0;
	if (signal(SIGINT, signal_handler) == SIG_ERR || \
		signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		print_error_and_exit("signal failure");
	rl_event_hook = handle_heredoc_sigint;
}

static void	readline_heredoc_loop(int fd[2], char *delimiter)
{
	char	*buf;

	while (1)
	{
		buf = readline("> ");
		if (!buf || ft_strcmp(buf, delimiter) == 0 || g_signum == SIGINT)
		{
			free(buf);
			break ;
		}
		buf = ft_strjoin_with_free(buf, "\n", FREE_FIRST_PARAM);
		if (!buf)
			print_error_and_exit("strjoin failure");
		write(fd[1], buf, ft_strlen(buf));
		free(buf);
	}
}

int	set_up_heredoc(t_redir *redir, t_data *d)
{
	int		fd[2];

	setup_heredoc_signal_handler();
	if (pipe(fd) == -1)
		print_error_and_exit("pipe failure");
	readline_heredoc_loop(fd, redir->delimiter);
	x_close(fd[1]);
	if (g_signum == SIGINT)
	{
		d->exit_status = 1;
		x_close(fd[0]);
		return (-1);
	}
	return (fd[0]);
}
