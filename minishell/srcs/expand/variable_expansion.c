/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 06:06:36 by myoshika          #+#    #+#             */
/*   Updated: 2024/04/12 04:18:26 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h> //free

static char	*get_id(char *ptr, size_t *i_mover)
{
	size_t	id_len;
	char	*id;

	id_len = 0;
	while (ft_isalnum(ptr[id_len]) || ptr[id_len] == '_')
		id_len++;
	id = ft_substr(ptr, 0, id_len);
	if (!id)
		print_error_and_exit("substr failure");
	*i_mover = id_len + 1;
	return (id);
}

static char	*expand_to_exit_status(size_t *i_mover, t_data *d)
{
	char	*exit_status;

	*i_mover = 2;
	exit_status = ft_itoa(d->exit_status);
	if (!exit_status)
		print_error_and_exit("itoa failure");
	return (exit_status);
}

char	*variable_expansion(char *ptr, size_t *i_mover, t_data *d)
{
	char	*id;
	char	*expanded_variable;
	t_env	*matching_env;

	if (*ptr == '?')
		return (expand_to_exit_status(i_mover, d));
	id = get_id(ptr, i_mover);
	matching_env = get_env(id, d->envp);
	free(id);
	if (matching_env)
		expanded_variable = x_strdup(matching_env->str);
	else
		expanded_variable = x_strdup("");
	return (expanded_variable);
}
