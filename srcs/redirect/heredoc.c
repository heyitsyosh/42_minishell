/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 20:30:10 by myoshika          #+#    #+#             */
/*   Updated: 2023/08/22 23:43:09 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"
#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include <readline/readline.h> //readline
#include <unistd.h> //write, pipe, close
#include <stdlib.h> //free

static void	readline_heredoc_loop(int fd[2], char *delimiter)
{
	char	*buf;

	while (1)
	{
		buf = readline("> ");
		if (!buf || ft_strcmp(buf, delimiter) == 0)
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

//handle readline interrupted
//fd[0] read end, fd[1] write end
int	set_up_heredoc(t_redir *redir)
{
	int		fd[2];

	if (pipe(fd) == -1)
		print_error_and_exit("pipe failure");
	readline_heredoc_loop(fd, redir->delimiter);
	if (close(fd[1]) == -1)
		print_error_and_exit("close failure");
	// if ()//readline interrupted
	// {
	// 	if (close(fd[0]) == -1)
	// 		print_error_and_exit("close failure");
	// 	return (-1);
	// }
	return (fd[0]);
}

//handle quoted vs unquoted delimiter?
//clear up question? abt hsano bigfile pipe buffer thingy