/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 05:08:00 by myoshika          #+#    #+#             */
/*   Updated: 2023/09/03 04:10:05 by myoshika         ###   ########.fr       */
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

void	exec_builtin(t_ast *builtin, t_data *d)
{
	const t_token	*list = builtin->cmd_list;
	const char		*cmd = list->word;

	if (!ft_strcmp("echo", cmd))
		d->exit_status = builtin_echo(list->next, d);
	if (!ft_strcmp("cd", cmd))
		d->exit_status = builtin_cd(list->next, d);
	if (!ft_strcmp("pwd", cmd))
		d->exit_status = builtin_pwd(list->next, d);
	if (!ft_strcmp("export", cmd))
		d->exit_status = builtin_export(list->next, d);
	if (!ft_strcmp("unset", cmd))
		d->exit_status = builtin_unset(list->next, d);
	if (!ft_strcmp("env", cmd))
		d->exit_status = builtin_env(list->next, d);
	if (!ft_strcmp("exit", cmd))
		d->exit_status = builtin_exit(list->next, d);
}
