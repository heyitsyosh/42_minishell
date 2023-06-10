/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 06:06:36 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/10 09:08:45 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft.h"

char	*variable_expansion(char *ptr, size_t **index_mover)
{
	char	*id;
	size_t	id_len;
	char	*expanded_variable;
	t_env	*matching_env;

	id_len = 0;
	while (ft_isalnum() || *ptr == '_')
		id_len++;
	id = ft_substr(ptr, 1, id_len);
	if (!id)
		print_error_and_exit("substr failure");
	matching_env = get_env(id, g_ms.envp_head);
	free(id);
	if (matching_env)
		expanded_variable = ft_strdup(matching_env->str);
	else
		expanded_variable = ft_strdup("");
	if (!expanded_variable)
		print_error_and_exit("substr failure");
	*index_mover = id_len + 1;
	return (expanded_variable);
}

size_t	no_interpretation_len(char *ptr, int status)
{
	size_t	len;

	len = 0;
	while (!ft_strchr("\\\"$", *ptr))
	{
		if (status == NOT_IN_DQUOTE && *ptr == "\'")
			break ;
		ptr++;
		len++;
	}
	return (len);
}
