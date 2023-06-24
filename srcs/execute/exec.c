/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:44:52 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/24 18:34:53 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include <unistd.h> //access
#include <stdlib.h> //free
#include <unistd.h> //fork
#include <sys/types.h> //pid_t
#include <sys/wait.h> //wait

void	execute_subshell(t_ast *ast)
{
	pid_t	pid;
	int		wait_status;

	pid = fork();
	if (pid == -1)
		print_error_and_exit("fork failure");
	if (pid == 0)
	{
		// set_up_redirect(ast->redir);
		execute(ast->left);
		// reset_redirect(ast->redir);
		exit(g_ms.exit_status);
	}
	wait(&wait_status);
	g_ms.exit_status = WEXITSTATUS(wait_status);
}
//emulate redirection (ex. (echo hello > out) > file)

void	execute_cmd(t_ast *cmd)
{
	if (cmd->cmd_list)
	{
		if (is_builtin(cmd->cmd_list->word))
			exec_builtin(cmd);
		else
			exec_nonbuiltin(cmd);
	}
}

void	execute(t_ast *ast)
{
	if (!ast)
		return ;
	else if (ast->type == CMD_NODE)
		execute_cmd(ast);
	if (ast->type == SUBSHELL_NODE)
		execute_subshell(ast);
	else if (ast->type == PIPE_NODE || ast->type == AND_NODE \
			|| ast->type == OR_NODE)
	{
		execute(ast->left);
		if ((ast->type == AND_NODE && g_ms.exit_status != 0) \
			|| (ast->type == OR_NODE && g_ms.exit_status == 0))
			return ;
		execute(ast->right);
	}
}
