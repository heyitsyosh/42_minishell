/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshono <cshono@student.42.tokyo>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 22:23:03 by myoshika          #+#    #+#             */
/*   Updated: 2022/12/14 01:28:03 by cshono           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./get_next_line.h"
# include "./ft_printf.h"

//envp interpreted as: <var>=<str>
typedef struct s_env{
	char			*var;
	char			*str;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_minishell{
	char	*line;
	t_env	*envp_head;
}	t_minishell;

void	init_shell(t_minishell *m, char **envp);

bool	str_is_num(char *str);

#endif
