/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:44:52 by myoshika          #+#    #+#             */
/*   Updated: 2023/09/05 22:47:43 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include <stdlib.h> //exit, EXIT_SUCCESS;

void	execute_subshell(t_ast *ast, t_pids **pid_list, t_data *d)
{
	pid_t	pid;

	pid = x_fork();
	if (pid == 0)
	{
		setup_child_signal_handler();
		if (!open_redir_files(ast->redir, IS_CHILD, d))
			exit(d->exit_status);
		set_up_redirect(ast->redir);
		if (ast->pipe_status == BESIDE_PIPE || ast->pipe_status == LAST_PIPE)
			close(ast->input_fd);
		execute(ast->left, d);
		reset_redirect(ast->redir);
		exit(d->exit_status);
	}
	if (ast->pipe_status == NO_PIPE)
		wait_one_child(pid, d);
	else
		add_pid(pid, pid_list, ast->pipe_status);
}

static void	exec_in_child(t_ast *cmd, t_pids **pid_list, t_data *d)
{
	pid_t	pid;

	pid = x_fork();
	if (pid == 0)
	{
		setup_child_signal_handler();
		if (cmd->pipe_status == BESIDE_PIPE || cmd->pipe_status == LAST_PIPE)
			close(cmd->input_fd);
		if (is_builtin(cmd->cmd_list->word))
			exec_builtin(cmd->cmd_list, d);
		else
			exec_nonbuiltin(cmd->cmd_list, d);
		exit(d->exit_status);
	}
	if (cmd->pipe_status == NO_PIPE)
		wait_one_child(pid, d);
	else
		add_pid(pid, pid_list, cmd->pipe_status);
}

void	execute_cmd(t_ast *cmd, t_pids **pid_list, t_data *d)
{
	if (!open_redir_files(cmd->redir, IS_PARENT, d))
		return ;
	set_up_redirect(cmd->redir);
	if (cmd->cmd_list)
	{
		d->exit_status = EXIT_SUCCESS;
		if (is_builtin(cmd->cmd_list->word) && cmd->pipe_status == NO_PIPE)
			exec_builtin(cmd->cmd_list, d);
		else
			exec_in_child(cmd, pid_list, d);
	}
	reset_redirect(cmd->redir);
}

void	execute(t_ast *ast, t_data *d)
{
	if (!ast)
		return ;
	else if (ast->type == CMD_NODE)
		execute_cmd(ast, NULL, d);
	else if (ast->type == SUBSHELL_NODE)
		execute_subshell(ast, NULL, d);
	else if (ast->type == PIPE_NODE)
		execute_pipeline(ast, d);
	else if (ast->type == AND_NODE || ast->type == OR_NODE)
	{
		execute(ast->left, d);
		if ((ast->type == AND_NODE && d->exit_status != 0) \
			|| (ast->type == OR_NODE && d->exit_status == 0))
			return ;
		execute(ast->right, d);
	}
}
