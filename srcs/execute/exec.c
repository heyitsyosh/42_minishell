/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:44:52 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/20 18:46:23 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft.h"

t_exec	*make_exec_struct(void)
{
	t_exec	*exec;

	exec = (t_exec *)malloc(sizeof(t_exec));
	if (!exec)
		print_error_and_exit("malloc failure");
	return (exec);
}

// static bool	needs_execution()
// {
	
// }

static void	execute(t_exec *exec, t_ast *ast)
{
	if (needs_execution())
	{
		set_up_redirect(ast);
		execute(ast);
		reset_redirect(ast);
	}
}
