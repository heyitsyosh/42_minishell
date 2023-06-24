/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 05:08:00 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/24 18:34:38 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libft.h"

static bool	is_builtin(char *cmd)
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
	
	//open_redir_files(builtin->redir);
	//set_up_redirect(builtin->redir);
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
	// reset_redirect(builtin->redir);
}
