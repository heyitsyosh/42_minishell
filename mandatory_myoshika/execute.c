/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 22:31:32 by myoshika          #+#    #+#             */
/*   Updated: 2022/12/25 18:12:25 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute(char *command, t_minishell *m)
{
	if (!ft_strcmp(command, "env"))
		builtin_env(m);
	else if (!ft_strcmp(command, "export"))
		builtin_export(m);
	else if (!ft_strcmp(command, "pwd"))
		builtin_pwd(m);
	else if (!ft_strcmp(command, "unset"))
		builtin_unset(m);
	else if (!ft_strcmp(command, "echo"))
		builtin_echo(m);
	else if (!ft_strcmp(command, "cd"))
		builtin_cd(m);
	else if (!ft_strcmp(command, "exit"))
		builtin_exit(m);
	else
		
}
