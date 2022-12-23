/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 22:23:03 by myoshika          #+#    #+#             */
/*   Updated: 2022/12/23 08:57:42 by myoshika         ###   ########.fr       */
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
	char			*id;
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

typedef enum e_type{
	GENERAL,
	QUOTE,
	DQUOTE,
	PIPE,
	GREATER,
	LESSER,
	HEREDOC,
	APPEND,
	AND,
	OR,
	LEFT_PARENTHESIS,
	RIGHT_PARENTHESIS,
	NIL,
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

void	init_envp(char **envp, t_minishell *m);

void	tokenize(char *line, t_minishell *m);
char	*extract_operator_token(char *cursor, t_token *t);

void	builtin_echo(char *str, bool new_line, t_minishell *m));
void	builtin_cd(char *line, t_minishell *m);
void	builtin_pwd(char *line, t_minishell *m);
void	builtin_export(char *line, t_minishell *m);
void	builtin_unset(char *id, t_minishell *m);
void	builtin_env(t_minishell *m);
void	builtin_exit(char *line, t_minishell *m);

t_env	*get_env(char *var, t_env *env);
void	free_envs(t_env *env);
void	env_add_back(t_env *envp, t_env *new_node);
t_env	*make_env_node(char	*envp);
char	**env_list_to_dbl_ptr(t_minishell *m);

#endif
