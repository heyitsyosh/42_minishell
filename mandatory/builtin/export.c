/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 22:31:32 by myoshika          #+#    #+#             */
/*   Updated: 2022/12/26 14:35:32 by myoshika         ###   ########.fr       */
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

static void	replace_str(t_env *matching_id, t_env *tmp)
{
	free(matching_id->str);
	matching_id->str = ft_strdup(tmp->str);
	if (!matching_id->str)
		exit(EXIT_FAILURE);
	free_envs(tmp);
}

static void	add_new_env(t_env *tmp, t_minishell *m)
{
	if (!m->envp_head)
	{
		m->envp_head = tmp;
		return ;
	}
	env_add_back(m->envp_head, tmp);
}

void	delete_escapes(char **str)
{
	while ((*str)[i])
}

void	builtin_export(char *line, t_minishell *m)
{
	t_env	*tmp;
	t_env	*matching_id;

	if (!ft_strchr(line, '='))
		return ;
	tmp = make_env_node(line);
	delete_escapes(&tmp->str);
	if (!is_valid_id(tmp->id))
	{
		ft_printf("export: '%s': not a valid identifier\n", line);
		free_envs(tmp);
		return ;
	}
	matching_id = get_env(tmp->id, m->envp_head);
	if (matching_id)
		replace_str(matching_id, tmp);
	else
		add_new_env(tmp, m);
}
