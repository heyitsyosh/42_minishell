/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:44:52 by myoshika          #+#    #+#             */
/*   Updated: 2023/09/04 04:38:52 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include <unistd.h> //access
#include <stdlib.h> //free, exit
#include <sys/types.h> //pid_t
#include <sys/wait.h> //wait

static void	execute_subshell(t_ast *ast, t_data *d)
{
	pid_t	pid;
	int		wait_status;

	pid = x_fork();
	if (pid == 0)
	{
		setup_child_signal_handler();
		if (!open_redir_files(ast->redir, IS_CHILD, d))
			return ;
		set_up_redirect(ast->redir);
		if (ast->pipe_status == BESIDE_PIPE)
			close(ast->input_fd);
		execute(ast->left, d);
		reset_redirect(ast->redir);
		exit(d->exit_status);
	}
	else
	{
		wait(&wait_status);
		d->exit_status = WEXITSTATUS(wait_status);
	}
}

static void	exec_in_child(t_ast *cmd, t_data *d)
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
			exec_builtin(cmd->cmd_list, d);
		else
			exec_nonbuiltin(cmd->cmd_list, d);
		exit(d->exit_status);
	}
	wait(&wait_status);
	d->exit_status = WEXITSTATUS(wait_status);
}

static void	execute_cmd(t_ast *cmd, t_data *d)
{
	if (!open_redir_files(cmd->redir, IS_PARENT, d))
		return ;
	set_up_redirect(cmd->redir);
	if (cmd->cmd_list)
	{
		if (is_builtin(cmd->cmd_list->word) && cmd->pipe_status == NO_PIPE)
			exec_builtin(cmd->cmd_list, d);
		else
			exec_in_child(cmd, d);
	}
	reset_redirect(cmd->redir);
}

static void	execute_pipeline(t_ast *ast, t_data *d)
{
	int	stdin_dup;
	int	input_fd;

	stdin_dup = x_dup(STDIN_FILENO);
	input_fd = run_left_of_pipe(ast, stdin_dup, d);
	run_right_of_pipe(ast->right, input_fd, d);
	close(stdin_dup);
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
