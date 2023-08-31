/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:44:52 by myoshika          #+#    #+#             */
/*   Updated: 2023/08/31 22:56:31 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include <unistd.h> //access
#include <stdlib.h> //free, exit
#include <sys/types.h> //pid_t
#include <sys/wait.h> //wait

static void	execute_subshell(t_ast *ast)
{
	pid_t	pid;
	int		wait_status;

	pid = x_fork();
	if (pid == 0)
	{
		setup_child_signal_handler();
		if (!open_redir_files(ast->redir, IS_CHILD))
			return ;
		set_up_redirect(ast->redir);
		if (ast->pipe_status == BESIDE_PIPE)
			close(ast->input_fd);
		execute(ast->left);
		reset_redirect(ast->redir);
		exit(g_ms.exit_status);
	}
	else
	{
		wait(&wait_status);
		g_ms.exit_status = WEXITSTATUS(wait_status);
	}
}

static void	exec_in_child(t_ast *cmd)
{
	pid_t	pid;
	int		wait_status;

	pid = x_fork();
	if (pid == 0)
	{
		setup_child_signal_handler();
		if (cmd->pipe_status == BESIDE_PIPE)
			close(cmd->input_fd);
		if (is_builtin(cmd->cmd_list->word))
			exec_builtin(cmd);
		else
			exec_nonbuiltin(cmd->cmd_list);
		exit(g_ms.exit_status);
	}
	wait(&wait_status);
	g_ms.exit_status = WEXITSTATUS(wait_status);
}

static void	execute_cmd(t_ast *cmd)
{
	if (!open_redir_files(cmd->redir, IS_PARENT))
		return ;
	set_up_redirect(cmd->redir);
	if (cmd->cmd_list)
	{
		if (is_builtin(cmd->cmd_list->word) && cmd->pipe_status == NO_PIPE)
			exec_builtin(cmd);
		else
			exec_in_child(cmd);
	}
	reset_redirect(cmd->redir);
}

void	execute(t_ast *ast)
{
	if (!ast)
		return ;
	else if (ast->type == CMD_NODE)
		execute_cmd(ast);
	else if (ast->type == SUBSHELL_NODE)
		execute_subshell(ast);
	else if (ast->type == PIPE_NODE)
		execute_pipeline(ast);
	else if (ast->type == AND_NODE || ast->type == OR_NODE)
	{
		execute(ast->left);
		if ((ast->type == AND_NODE && g_ms.exit_status != 0) \
			|| (ast->type == OR_NODE && g_ms.exit_status == 0))
			return ;
		execute(ast->right);
	}
}
