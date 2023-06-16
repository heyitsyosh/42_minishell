/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:47:28 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/16 23:53:12 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft.h"
#include <stdlib.h> //malloc

void	make_cmd_struct(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc((sizeof)t_cmd);
	if (!cmd)
		print_error_and_exit("malloc failure");
	cmd->command = NULL;
	cmd->args = NULL;
	return (cmd);
}

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

static void	convert_nodes_to_dbl_ptr(char **args, t_token *tmp_args)
{
	size_t	i;

	i = 0;
	while (tmp_args)
	{
		*(args + i) = ft_strdup(tmp_args->word);
		if (!*(args + i))
			print_error_and_exit("strdup failure");
		tmp_args = tmp_args->next;
		i++;
	}
	*(args + i) = NULL;
}

void	arg_list_to_dbl_ptr(t_ast *cmd_node, t_parse *p)
{
	size_t	malloc_size;

	if (!p->tmp_args)
		return ;
	cmd_node->cmd = make_cmd_struct();
	cmd_node->cmd->args = (char **)malloc(count_malloc_size(p->tmp_args) + 1);
	if (!cmd_node->cmd->args)
		print_error_and_exit("malloc failure");
	convert_nodes_to_dbl_ptr(cmd_node->cmd->args, p->tmp_args);
	free_tokens(p->tmp_args);
	p->tmp_args = NULL;
}
