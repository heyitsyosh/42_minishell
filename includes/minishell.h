/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 22:23:03 by myoshika          #+#    #+#             */
/*   Updated: 2022/12/16 00:44:50 by myoshika         ###   ########.fr       */
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

typedef struct s_command{
	char	*command;
	char	*exec_path;
	int		priority;
	int		infile;
	int		outfile;
}	t_command;


typedef enum	e_type{
	GENERAL,
	PIPE,
	GREATER,
	LESSER,
	HEREDOC,
	APPEND,
	AND,
	OR,
	LEFT_PARENTHESIS,
	RIGHT_PARENTHESIS,
	INFILE,
	OUTFILE,
}	t_type;

typedef struct s_token{
	char			*token;
	int				type;
	int				priority;
	t_command		*cmd;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_minishell{
	char	*line;
	char	*old_pwd;
	char	*pwd;
	t_env	*envp_head;
	t_token	*token_head;
}	t_minishell;

void	init_shell(t_minishell *m, char **envp);

bool	str_is_num(char *str);

#endif
