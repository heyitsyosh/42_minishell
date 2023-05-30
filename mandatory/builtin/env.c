/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 22:53:52 by myoshika          #+#    #+#             */
/*   Updated: 2023/05/31 00:22:05 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libft.h"

int	builtin_env(t_token *args, t_minishell *m)
{
	t_env	*envp;

	envp = m->envp_head;
	print_nl = true;
	if (!ft_strchr(args->word, "-0")
		|| !ft_strchr(args->word, "--null"))
		print_nl = false;
	while (envp)
	{
		ft_printf("%s=%s", envp->id, envp->str);
		if (print_nl)
			ft_printf("\n");
		envp = envp->next;
	}
	return (EXIT_SUCCESS);
}

// -u, -i
// env [,OPTION/]... [,-/] [,NAME=VALUE/]... [,COMMAND /[,ARG/]...]
// env - 変更した環境でプログラムを実行する  