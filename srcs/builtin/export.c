/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 22:31:32 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/12 02:07:09 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include <stdlib.h> //malloc, free, exit, EXIT_SUCCESS, EXIT_FAILURE

static void	add_new_env(t_env *tmp)
{
	if (!g_ms.envp_head)
	{
		g_ms.envp_head = tmp;
		return ;
	}
	env_add_back(g_ms.envp_head, tmp);
}

static void	copy_without_escaped_chars(char *str_to_change, char *str)
{
	while (*str)
	{
		if (*str == '\\' && ft_strchr(*(str + 1), "\"$"))
			i++;
		*str_to_change = *str;
		str++;
		str_to_change++;
	}
}

static void	delete_escapes(char **str_to_change, char *str)
{
	size_t	i;
	size_t	new_len;

	i = 0;
	new_len = 0;
	while (str[i])
	{
		if (str[i] == '\\' && ft_strchr(str[i + 1], "\"$"))
			i++;
		new_len++;
		i++;
	}
	free(*str_to_change);
	*str_to_change = (char *)malloc(new_len + 1);
	if (!(*str_to_change))
		print_error_and_exit("malloc failure");
	copy_without_escaped_chars(*str_to_change, str);
	free(str);
}

static void	export_env(t_env *tmp)
{
	t_env	*matching_id;

	delete_escapes(&tmp->str, ft_strdup(tmp->str));
	matching_id = get_env(tmp->id, g_ms.envp_head);
	if (matching_id)
	{
		free(matching_id->str);
		matching_id->str = ft_strdup(tmp->str);
		if (!matching_id->str)
			print_error_and_exit("strdup failure");
		free_envs(tmp);
	}
	else
		add_new_env(tmp);
}

int	builtin_export(t_token *args)
{
	int		status;
	t_env	*tmp;

	status = EXIT_SUCCESS;
	if (!args)
		export_no_args();
	while (args)
	{
		if (ft_strchr(args->word, '='))
		{
			tmp = make_env_node(args->word);
			if (!is_valid_id(tmp->id))
			{
				if (status != EXIT_FAILURE)
					msg_to_stderr("export: ", args->word, \
					": not a valid identifier\n");
				status = EXIT_FAILURE;
				free_envs(tmp);
				continue ;
			}
			export_env(tmp);
		}
		args = args->next;
	}
	return (status);
}
