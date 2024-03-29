/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:47:28 by myoshika          #+#    #+#             */
/*   Updated: 2023/09/07 16:50:36 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include <stdlib.h> //malloc

static size_t	get_malloc_size(t_token *cmd_list)
{
	size_t	size;

	size = 0;
	while (cmd_list)
	{
		size++;
		cmd_list = cmd_list->next;
	}
	return (size);
}

static void	tok_list_to_dbl_ptr(char **argv, t_token *cmd_list)
{
	size_t	i;

	i = 0;
	while (cmd_list)
	{
		argv[i] = x_strdup(cmd_list->word);
		cmd_list = cmd_list->next;
		i++;
	}
	argv[i] = NULL;
}

char	**make_argv_from_list(t_token *cmd_list)
{
	char	**argv;

	argv = (char **)malloc((get_malloc_size(cmd_list) + 1) * sizeof(char *));
	if (!argv)
		print_error_and_exit("malloc failure");
	tok_list_to_dbl_ptr(argv, cmd_list);
	return (argv);
}
