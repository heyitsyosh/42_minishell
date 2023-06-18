/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:47:28 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/19 02:52:00 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include <stdlib.h> //malloc


static size_t	count_malloc_size(t_token *tmp_args)
{
	size_t	size;

	size = 0;
	while (tmp_args)
	{
		size++;
		tmp_args = tmp_args->next;
	}
	return (size);
}

static void	tok_list_to_dbl_ptr(char **args, t_token *arg_list)
{
	size_t	i;

	i = 0;
	while (arg_list)
	{
		*(args + i) = ft_strdup(arg_list->word);
		if (!*(args + i))
			print_error_and_exit("strdup failure");
		arg_list = arg_list->next;
		i++;
	}
	*(args + i) = NULL;
}

void	arg_list_to_dbl_ptr(t_ast *cmd_node)
{
	size_t	malloc_size;

	if (arg_list)
		return ;
	cmd_node->cmd->args = (char **)malloc(count_malloc_size(p->tmp_args) + 1);
	if (!cmd_node->cmd->args)
		print_error_and_exit("malloc failure");
	convert_nodes_to_dbl_ptr(cmd_node->cmd->args, p->tmp_args);
	free_tokens(p->tmp_args);
	p->tmp_args = NULL;
}
