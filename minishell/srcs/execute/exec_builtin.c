/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 05:08:00 by myoshika          #+#    #+#             */
/*   Updated: 2023/09/03 21:55:04 by myoshika         ###   ########.fr       */
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

void	exec_builtin(t_token *cmd_list, t_data *d)
{
	const char		*cmd = cmd_list->word;
	t_token			*args;

	args = cmd_list->next;
	if (!ft_strcmp("echo", cmd))
		d->exit_status = builtin_echo(args, d);
	if (!ft_strcmp("cd", cmd))
		d->exit_status = builtin_cd(args, d);
	if (!ft_strcmp("pwd", cmd))
		d->exit_status = builtin_pwd(args, d);
	if (!ft_strcmp("export", cmd))
		d->exit_status = builtin_export(args, d);
	if (!ft_strcmp("unset", cmd))
		d->exit_status = builtin_unset(args, d);
	if (!ft_strcmp("env", cmd))
		d->exit_status = builtin_env(args, d);
	if (!ft_strcmp("exit", cmd))
		d->exit_status = builtin_exit(args, d);
}
