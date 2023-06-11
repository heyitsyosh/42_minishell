/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 22:54:02 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/10 11:36:57 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int	cd_with_no_args(void)
// {
// 	t_env	*home;

// 	home = getenv("HOME");
// 	if (!home)
// 	{
// 		ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
// 		return (EXIT_FAILURE);
// 	}
	
// }

// get_chdir_destination(t_token *args)

char	*get_relative_path(char	*given)
{
	
}

int	builtin_cd(t_token *args)
{
	char	*path;

	if (args && args->next)
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (args && *args->word == '/')
		path = args->word;
	else
		path = get_relative_path(args);
}

//chdir segfault??
//delete directory and, ENV kakikaeru junban
//no args
//~
//no $HOME?
//rewrite env oldpwd, pwd
//shell vars vs env vars
/*
types of error messages according to chatgpt
"No such file or directory": This error message occurs when the specified directory does not exist in the file system.
"Permission denied": This error message is displayed when the current user does not have the necessary permissions to access the specified directory.
"Not a directory": This error message is shown when the path provided is not a directory, but rather a file or another type of object.
"Too many symbolic links": This error message is displayed when resolving symbolic links results in a loop, reaching the maximum number of symbolic link traversals.
"Invalid argument": This error message can appear if the argument passed to cd is not valid or well-formed.
"Home directory not set": This error message may occur if the home directory of the current user is not properly set or cannot be determined.
*/