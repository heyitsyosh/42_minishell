/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 22:31:32 by myoshika          #+#    #+#             */
/*   Updated: 2024/04/12 04:19:07 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_printf.h"
#include "libft.h"
#include <stdlib.h> //malloc, free, exit, EXIT_SUCCESS, EXIT_FAILURE

static void	export_no_args(t_env *envp)
{
	while (envp)
	{
		ft_printf("declare -x %s=\"%s\"\n", envp->id, envp->str);
		envp = envp->next;
	}
}

static void	export_env(t_env *tmp, t_data *d)
{
	t_env	*matching_id;

	matching_id = get_env(tmp->id, d->envp);
	if (matching_id)
	{
		replace_env_str(matching_id, x_strdup(tmp->str));
		free_envs(tmp);
	}
	else
		add_new_env(tmp, d);
}

int	builtin_export(t_token *args, t_data *d)
{
	int		status;
	t_env	*tmp;

	status = EXIT_SUCCESS;
	if (!args)
		export_no_args(d->envp);
	while (args)
	{
		if (ft_strchr(args->word, '='))
		{
			tmp = make_env_node(args->word);
			if (!is_valid_id(tmp->id))
			{
				if (status != EXIT_FAILURE)
					err_msg("export: ", args->word, ": not a valid identifier");
				status = EXIT_FAILURE;
				free_envs(tmp);
				args = args->next;
				continue ;
			}
			export_env(tmp, d);
		}
		args = args->next;
	}
	return (status);
}
