/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 22:31:32 by myoshika          #+#    #+#             */
/*   Updated: 2023/09/03 07:52:16 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/ft_printf.h"
#include "../../includes/libft.h"
#include <stdlib.h> //malloc, free, exit, EXIT_SUCCESS, EXIT_FAILURE

static void	export_no_args(t_env *envp)
{
	while (envp)
	{
		ft_printf("declare -x %s=\"%s\"\n", envp->id, envp->str);
		envp = envp->next;
	}
}

static void	copy_without_escaped_chars(char *no_escape_str, char *str)
{
	while (*str)
	{
		if (*str == '\\' && ft_strchr("\"$", *(str + 1)))
			str++;
		*no_escape_str = *str;
		no_escape_str++;
		str++;
	}
	*no_escape_str = '\0';
}

static void	delete_escapes(char **no_escape_str, char *str)
{
	size_t	i;
	size_t	new_len;

	i = 0;
	new_len = 0;
	while (str[i])
	{
		if (str[i] == '\\' && ft_strchr("\"$", str[i + 1]))
			i++;
		new_len++;
		i++;
	}
	free(*no_escape_str);
	*no_escape_str = (char *)malloc(new_len + 1);
	if (!(*no_escape_str))
		print_error_and_exit("malloc failure");
	copy_without_escaped_chars(*no_escape_str, str);
	free(str);
}

static void	export_env(t_env *tmp, t_data *d)
{
	t_env	*matching_id;

	delete_escapes(&tmp->str, x_strdup(tmp->str));
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
					msg_to_stderr("export: ", args->word, \
					": not a valid identifier\n");
				status = EXIT_FAILURE;
				free_envs(tmp);
				continue ;
			}
			export_env(tmp, d);
		}
		args = args->next;
	}
	return (status);
}
