/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 22:31:32 by myoshika          #+#    #+#             */
/*   Updated: 2022/12/19 19:58:12 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool is_valid_id(char *id)
{
	if ((!ft_isalpha(*id) && *id != '_') || !ft_strchr(id, '='))
		return (false);
    while (*id && *id != '=')
    {
        if (!ft_isalnum(*id) && *id != '_')
            return (false);
        id++;
    }
    return (true);
}

replace_

void	builtin_export(char *line, t_minishell *m)
{
	t_env	*tmp;
	t_env	*matching_id;

	tmp = make_env_node(line);
	if (!tmp || tmp->id || tmp->str)
		exit(EXIT_FAILURE);
    if (!is_valid_id(tmp->id))
    {
        free_envs(tmp);
        return ;
    }
	matching_id = get_env(tmp->id, m->envp_head);
	if (!m->envp_head)
	{
		m->envp_head = tmp;
		return ;
	}
	if (matching_id)
	{
		free(matching_id->str);
		matching_id->str = ft_strdup(tmp->str);
        if (!matching_id->str)
           exit(EXIT_FAILURE); 
		free_envs(tmp);
	}
	else
		env_add_back(m->envp_head, tmp);
}
