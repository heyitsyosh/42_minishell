/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 06:06:36 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/11 22:14:52 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft.h"
#include "../includes/get_next_line.h"

char	*expand_to_exit_status(size_t **index_mover)
{
	char	*exit_status;

	*index_mover = 2;
	exit_status = ft_itoa(g_ms.status);
	if (!exit_status)
		print_error_and_exit("itoa failure");
	return (exit_status);
}

char	*variable_expansion(char *ptr, size_t **index_mover)
{
	char	*id;
	size_t	id_len;
	char	*expanded_variable;
	t_env	*matching_env;

	id_len = 0;
	if (*ptr == '?')
		return (expand_to_exit_status(index_mover));
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
		if (status == NOT_IN_DQUOTE && (*ptr == "\'" || *ptr == "*"))
			break ;
		ptr++;
		len++;
	}
	return (len);
}

char	*no_interpretation_if_not_closed(char *str, char **ptr, size_t i)
{
	if (**ptr != (*ptr)[i])
	{
		free(str);
		str = ft_substr(*ptr, 0, 1);
		*ptr += 1;
	}
	else
	{
		if (**ptr == '\'')
			str = ft_strjoin_with_free(str, "\'", FREE_FIRST_PARAM);
		else
			str = ft_strjoin_with_free(str, "\"", FREE_FIRST_PARAM);
		*ptr += i + 1;
	}
	return (str);
}
