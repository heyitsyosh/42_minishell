/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 06:06:36 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/15 18:22:18 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/expand.h"
#include "../../includes/libft.h"
#include <stdlib.h> //free

static char	*get_id(char *ptr, size_t *index_mover)
{
	size_t	id_len;
	char	*id;

	id_len = 0;
	while (ft_isalnum(ptr[id_len]) || ptr[id_len] == '_')
		id_len++;
	id = ft_substr(ptr, 1, id_len);
	if (!id)
		print_error_and_exit("substr failure");
	*index_mover = id_len + 1;
	return (id);
}

static char	*expand_to_exit_status(size_t *index_mover)
{
	char	*exit_status;

	*index_mover = 2;
	exit_status = ft_itoa(g_ms.exit_status);
	if (!exit_status)
		print_error_and_exit("itoa failure");
	return (exit_status);
}

char	*variable_expansion(char *ptr, size_t *index_mover)
{
	char	*id;
	char	*expanded_variable;
	t_env	*matching_env;

	if (*ptr == '?')
		return (expand_to_exit_status(index_mover));
	id = get_id(ptr, index_mover);
	matching_env = get_env(id, g_ms.envp_head);
	free(id);
	if (matching_env)
		expanded_variable = ft_strdup(matching_env->str);
	else
		expanded_variable = ft_strdup("");
	if (!expanded_variable)
		print_error_and_exit("substr failure");
	return (expanded_variable);
}
