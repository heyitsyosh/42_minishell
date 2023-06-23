/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 22:54:08 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/23 13:00:03 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include <stdlib.h> //free, EXIT_SUCCESS, EXIT_FAILURE

bool	is_valid_id(char *id)
{
	if ((!ft_isalpha(*id) && *id != '_'))
		return (false);
	while (*id && *id != '=')
	{
		if (!ft_isalnum(*id) && *id != '_')
			return (false);
		id++;
	}
	return (true);
}

static void	delete_env(t_env *to_delete)
{
	t_env	*next_env;
	t_env	*prev_env;

	next_env = to_delete->next;
	prev_env = to_delete->prev;
	if (prev_env)
		prev_env->next = next_env;
	if (next_env)
		next_env->prev = prev_env;
	free(to_delete);
}

int	builtin_unset(t_token *args)
{
	t_env	*matching_id;
	int		status;

	status = EXIT_SUCCESS;
	while (args)
	{
		matching_id = (get_env(args->word));
		if (!(is_valid_id(args->word)))
		{
			if (status != EXIT_FAILURE)
				msg_to_stderr("export: ", args->word, \
					": not a valid identifier\n");
			status = EXIT_FAILURE;
		}
		else if (matching_id)
		{
			if (matching_id == g_ms.envp_head)
				g_ms.envp_head = matching_id->next;
			delete_env(matching_id);
		}
		args = args->next;
	}
	return (status);
}
