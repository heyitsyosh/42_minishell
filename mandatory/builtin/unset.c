/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 22:54:08 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/08 02:11:23 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	builtin_unset(t_token *args, t_minishell *m)
{
	t_env	*matching_id;
	int		status;

	status = EXIT_SUCCESS;
	while (args)
	{
		matching_id = (get_env(args->word, m->envp_head));
		if (!(is_valid_id(args->word)))
		{
			if (status != EXIT_FAILURE)
				printf("unset: `%s': not a valid identifier", args->word);
			status = EXIT_FAILURE;
		}
		else if (matching_id)
		{
			if (matching_id == m->envp_head)
				m->envp_head = matching_id->next;
			delete_env(matching_id);
		}
		args = args->next;
	}
	return (status);
}
