/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_update_pwd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 20:42:50 by myoshika          #+#    #+#             */
/*   Updated: 2023/09/04 21:33:42 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libft.h"

static void	make_pwd_path()
{
	
}

void	update_pwd(char *path, t_token *dir, t_data *d)
{
	t_env	*pwd;
	t_char	*to_be_pwd;

	pwd = get_env("PWD", d->envp);
	if (!pwd)
		pwd = make_env_node("PWD=");
	if (!expand_to_home(dir))
		make_pwd_path(to_be_pwd, dir);
	replace_env_str(pwd, x_strdup(to_be_pwd));
	free(d->pwd);
	d->pwd = to_be_pwd;
}
