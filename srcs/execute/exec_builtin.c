/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 05:08:00 by myoshika          #+#    #+#             */
/*   Updated: 2023/08/31 13:41:13 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libft.h"

bool	is_builtin(char *cmd)
{
	if (!ft_strcmp("echo", cmd) \
		|| !ft_strcmp("cd", cmd) \
		|| !ft_strcmp("pwd", cmd) \
		|| !ft_strcmp("export", cmd) \
		|| !ft_strcmp("unset", cmd) \
		|| !ft_strcmp("env", cmd) \
		|| !ft_strcmp("exit", cmd))
		return (true);
	return (false);
}

void	exec_builtin(t_ast *builtin)
{
	const t_token	*list = builtin->cmd_list;
	const char		*cmd = list->word;


	if (!ft_strcmp("echo", cmd))
		g_ms.exit_status = builtin_echo(list->next);
	if (!ft_strcmp("cd", cmd))
		g_ms.exit_status = builtin_cd(list->next);
	if (!ft_strcmp("pwd", cmd))
		g_ms.exit_status = builtin_pwd(list->next);
	if (!ft_strcmp("export", cmd))
		g_ms.exit_status = builtin_export(list->next);
	if (!ft_strcmp("unset", cmd))
		g_ms.exit_status = builtin_unset(list->next);
	if (!ft_strcmp("env", cmd))
		g_ms.exit_status = builtin_env(list->next);
	if (!ft_strcmp("exit", cmd))
		g_ms.exit_status = builtin_exit(list->next);
}
