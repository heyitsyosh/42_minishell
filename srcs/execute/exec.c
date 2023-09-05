/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:44:52 by myoshika          #+#    #+#             */
/*   Updated: 2023/09/05 19:03:46 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include <unistd.h> //access
#include <stdlib.h> //free, exit
#include <sys/types.h> //pid_t
#include <sys/wait.h> //wait

pid_t	execute_subshell(t_ast *subshell, t_data *d)
{
	pid_t	pid;

	pid = x_fork();
	if (pid == 0)
	{
		setup_child_signal_handler();
		if (!open_redir_files(subshell->redir, IS_CHILD, d))
			exit(d->exit_status);
		set_up_redirect(subshell->redir);
		if (subshell->pipe_status == BESIDE_PIPE)
			close(subshell->input_fd);
		execute(subshell->left, d);
		reset_redirect(subshell->redir);
		exit(d->exit_status);
	}
	wait_for_no_pipe(subshell, pid, d);
	return (pid);
}

static pid_t	exec_in_child(t_ast *cmd, t_data *d)
{
	pid_t	pid;

	pid = x_fork();
	if (pid == 0)
	{
		setup_child_signal_handler();
		if (cmd->pipe_status == BESIDE_PIPE)
			close(cmd->input_fd);
		if (is_builtin(cmd->cmd_list->word))
			exec_builtin(cmd->cmd_list, d);
		else
			exec_nonbuiltin(cmd->cmd_list, d);
		exit(d->exit_status);
	}
	wait_for_no_pipe(cmd, pid, d);
	return (pid);
}

pid_t	execute_cmd(t_ast *cmd, t_data *d)
{
	pid_t	pid;

	pid = NO_PID;
	if (!open_redir_files(cmd->redir, IS_PARENT, d))
		return (pid);
	set_up_redirect(cmd->redir);
	if (cmd->cmd_list)
	{
		d->exit_status = EXIT_SUCCESS;
		if (is_builtin(cmd->cmd_list->word) && cmd->pipe_status == NO_PIPE)
			exec_builtin(cmd->cmd_list, d);
		else
			pid = exec_in_child(cmd, d);
	}
	reset_redirect(cmd->redir);
	return (pid);
}

void	execute_pipeline(t_ast *ast, t_data *d)
{
	int		stdin_dup;
	int		input_fd;
	pid_t	last_pid;

	stdin_dup = x_dup(STDIN_FILENO);
	input_fd = run_left_of_pipe(ast, stdin_dup, d);
	last_pid = run_right_of_pipe(ast->right, input_fd, d);
	close(stdin_dup);
	wait_for_last_child(last_pid, d);
}

void	execute(t_ast *ast, t_data *d)
{
	if (!ast)
		return ;
	else if (ast->type == CMD_NODE)
		execute_cmd(ast, d);
	else if (ast->type == SUBSHELL_NODE)
		execute_subshell(ast, d);
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
