/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 05:08:00 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/23 08:50:42 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include <unistd.h> //fork
#include <sys/types.h> //pid_t
#include <sys/wait.h> //wait

static bool	is_builtin(t_token *cmd_list)
{
	if (!cmd_list)
		return (false);
	else if (!ft_strcmp("echo", cmd_list) \
			|| !ft_strcmp("cd", cmd_list) \
			|| !ft_strcmp("pwd", cmd_list) \
			|| !ft_strcmp("export", cmd_list) \
			|| !ft_strcmp("unset", cmd_list) \
			|| !ft_strcmp("env", cmd_list) \
			|| !ft_strcmp("exit", cmd_list))
		return (true);
	return (false);
}

void	exec_builtin(t_token *cmd_list)
{
	if (!ft_strcmp("echo", cmd_list))
		g_ms.exit_status = builtin_echo(cmd_list->next);
	if (!ft_strcmp("cd", cmd_list))
		g_ms.exit_status = builtin_cd(cmd_list->next);
	if (!ft_strcmp("pwd", cmd_list))
		g_ms.exit_status = builtin_pwd(cmd_list->next);
	if (!ft_strcmp("export", cmd_list))
		g_ms.exit_status = builtin_export(cmd_list->next);
	if (!ft_strcmp("unset", cmd_list))
		g_ms.exit_status = builtin_unset(cmd_list->next);
	if (!ft_strcmp("env", cmd_list))
		g_ms.exit_status = builtin_env(cmd_list->next);
	if (!ft_strcmp("exit", cmd_list))
		g_ms.exit_status = builtin_exit(cmd_list->next);
}

void	execute_cmd(t_ast *cmd)
{
	pid_t	pid;
	int		wait_status;

	pid = fork();
	if (pid == -1)
		print_error_and_exit("fork failure");
	else if (pid == 0)
	{
		set_up_redirect(cmd->redir);
		if (is_builtin(cmd->cmd_list))
			exec_builtin(cmd->cmd_list);
		else if (cmd->cmd_list)
			exec_execve(cmd->cmd_list);
		reset_redirect(cmd->redir);
	}
	else
		wait(&wait_status);
}
