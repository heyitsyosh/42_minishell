/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 22:23:03 by myoshika          #+#    #+#             */
/*   Updated: 2023/05/25 18:08:27 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <stdio.h>

extern volatile sig_atomic_t	g_status;
typedef enum e_token_type
{
	WORD,
	IO_NUMBER,
	AND,
	OR,
	REDIR_APPEND,
	HEREDOC,
	REDIR_OUT,
	REDIR_IN,
	OPEN_PARENTHESIS,
	CLOSE_PARENTHESIS,
	PIPE,
	NIL,
}	t_token_type;

typedef struct s_token
{
	char			*word;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef enum e_type
{
	SIMPLE_COMMAND,
}	t_type;

typedef struct s_env{
	char			*id;
	char			*str;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_minishell{
	bool	is_interactive_mode;
	char	*old_pwd;
	char	*pwd;
	t_env	*envp_head;
}	t_minishell;

typedef struct s_parse{
	t_token	*current_tok;
}	t_parse;

// Redirecting output example
//command          : "echo hello; 1 > out"
// targetfd         : 1
// filename         : "out"
// filefd           : open("out")
// stashed_targetfd : dup(targetfd)

// typedef struct s_redir
// {
// 	int		left;
// 	int		right;
// 	char	*filename;
// 	int		file_fd;
// 	int		stashed_fd;
// }	t_redir;

typedef struct s_ast_node
{
	t_token				*token;
	struct s_ast_node	*left_child;
	struct s_ast_node	*right_child;
	//t_redir			*redir;
}	t_ast_node;

/*typedef struct s_node
{
	t_type			type;
	t_token			*args;
	t_redir			*redir;
	struct s_node	*next;
}	t_node; */

void		init_envp(char **envp, t_minishell *m);
t_env		*get_env(char *var, t_env *env);
void		free_envs(t_env *env);
void		env_add_back(t_env *envp, t_env *new_node);
t_env		*make_env_node(char	*envp);
char		**env_list_to_dbl_ptr(t_minishell *m);

bool		is_blank(char c);
bool		is_operator(char c);

void		print_error_and_exit(char *error_message);
void		print_syntax_error(char *unexpected_token);

t_token		*tokenize(char *line);
t_ast_node	*parser(t_token *tok);
// void	expand(t_node *node);
// void	execute(t_node *node);

int			builtin_echo(char *str, bool new_line);
int			builtin_unset(char *id, t_minishell *m);
int			builtin_export(char *line, t_minishell *m);
int			builtin_exit(char *line, t_minishell *m);
int			builtin_cd(char *line, t_minishell *m);
int			builtin_pwd(t_minishell *m);
int			builtin_env(t_minishell *m);

t_token		*make_token(char *word, t_token_type type);
t_ast_node	*make_ast_node(t_token *token);

void		free_tokens(t_token *tok);

#endif
