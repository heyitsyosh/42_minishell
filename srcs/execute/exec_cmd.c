/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 05:08:00 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/23 11:50:50 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include <unistd.h> //fork
#include <sys/types.h> //pid_t
#include <sys/wait.h> //wait

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

void	exec_builtin(t_token *cmd_list)
{
	char	*cmd;

	cmd = cmd_list->word;
	if (!ft_strcmp("echo", cmd))
		g_ms.exit_status = builtin_echo(cmd_list->next);
	if (!ft_strcmp("cd", cmd))
		g_ms.exit_status = builtin_cd(cmd_list->next);
	if (!ft_strcmp("pwd", cmd))
		g_ms.exit_status = builtin_pwd(cmd_list->next);
	if (!ft_strcmp("export", cmd))
		g_ms.exit_status = builtin_export(cmd_list->next);
	if (!ft_strcmp("unset", cmd))
		g_ms.exit_status = builtin_unset(cmd_list->next);
	if (!ft_strcmp("env", cmd))
		g_ms.exit_status = builtin_env(cmd_list->next);
	if (!ft_strcmp("exit", cmd))
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
		// set_up_redirect(cmd->redir);
		if (cmd->cmd_list)
		{
			if (is_builtin(cmd->cmd_list->word))
				exec_builtin(cmd->cmd_list);
			else
				exec_execve(cmd->cmd_list);
		}
		// reset_redirect(cmd->redir);
	}
	else
		wait(&wait_status);
}
