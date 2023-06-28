/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 22:23:03 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/25 18:44:21 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <stddef.h> //size_t
# include <signal.h> //sig_atomic_t
#include <stdio.h>

# define NOT_IN_DQUOTE 0
# define IN_DQUOTE 1

typedef struct s_env{
	char			*id;
	char			*str;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef enum e_token_type
{
	WORD,
	IO_NUMBER,
	PIPE,
	AND,
	OR,
	RD_APPEND,
	RD_HEREDOC,
	RD_IN,
	RD_OUT,
	OPEN_PARENTHESIS,
	CLOSE_PARENTHESIS,
	UNSET,
}	t_token_type;

typedef struct s_token
{
	char			*word;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef enum e_ast_node_type
{
	SUBSHELL_NODE,
	PIPE_NODE,
	AND_NODE,
	OR_NODE,
	CMD_NODE,
}	t_ast_node_type;

typedef struct s_redir
{
	char			*filename;
	int				file_fd;
	int				target_fd;
	int				stashed_target_fd;
	bool			io_num_used;
	int				io_num;
	char			*delimitor;
	t_token_type	type;
	struct s_redir	*prev;
	struct s_redir	*next;
}	t_redir;

typedef struct s_ast
{
	t_ast_node_type	type;
	t_token			*cmd_list;
	t_redir			*redir;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

//global struct//
typedef struct s_minishell{
	bool					is_interactive_mode;
	int						exit_status;
	char					*pwd;
	t_env					*envp_head;
	volatile sig_atomic_t	signum;
}	t_minishell;

extern t_minishell	g_ms;

/* init_envp.c */
void			init_envp(char **envp);

/* tokenize.c */
t_token			*tokenize(char *line);

/* tokenize_utils.c */
bool			is_blank(char c);
bool			is_operator(char c);
bool			is_io_number(char *line);
t_token_type	get_operator_type(char *operator);
t_token			*make_token(char *word, t_token_type type);

/* expand.c */
void			expand(t_token *tok);

/* parse.c */
t_ast			*parser(t_token *tok);
t_ast			*create_ast(t_token **tok, char **syntax_err);
t_ast			*parse_and_or(t_token **tok, char **syntax_err);
t_ast			*parse_subshell(t_token **tok, char **syntax_err);

/* parse_cmd.c */
t_ast			*parse_cmd(t_token **tok, char **syntax_err);
void			add_redirection(t_token **tok, t_ast *cmd_node);

/* parse_redirect.c */
void			parse_redir(t_token **tok, t_ast *node, char **syntax_err);

/* parse_redirect_utils.c */
void			add_redir_to_list(t_ast *node, t_redir *redir_to_add);
t_redir			*make_redir_struct(void);

/* parse_utils.c */
bool			is_redir(t_token *tok);
bool			is_unexpected(t_token *next);
t_ast			*set_syntax_error(t_token *tok, char **syntax_err);
t_ast			*make_ast_node(t_ast_node_type type, t_ast *lhs, t_ast *rhs);
bool			tok_is(t_token_type type, t_token *tok);

/* exec */
void			execute(t_ast *ast);
void			execute_cmd(t_ast *cmd);
void			execute_subshell(t_ast *ast);

/* exec_builtin */
bool			is_builtin(char *cmd);
void			exec_builtin(t_ast *cmd);

/* exec_nonbuiltin */
void			exec_nonbuiltin(t_token *cmd_list);

/* redirect */
bool			open_redir_files(t_redir *redir);

/* make_argv */
char			**make_argv_from_list(t_token *cmd_list);

/* builtins */
int				builtin_echo(t_token *args);
int				builtin_cd(t_token *args);
int				builtin_pwd(t_token *args);
int				builtin_export(t_token *args);
int				builtin_unset(t_token *args);
int				builtin_env(t_token *args);
int				builtin_exit(t_token *args);

bool			is_valid_id(char *id);
void			export_no_args(void);

/* env_utils.c */
t_env			*get_env(char *var);
void			env_add_back(t_env *envp, t_env *new_node);
void			replace_env_str(t_env *env, char *new_str);
t_env			*make_env_node(char	*envp);
char			**make_envp_from_list(void);

/* error.c */
void			print_error_and_exit(char *error_message);
void			print_syntax_error(char *unexpected_token);
void			msg_to_stderr(char *first, char *second, char *third);

/* free.c */
void			free_tokens(t_token *tok);
void			free_envs(t_env *env);
void			free_ast(t_ast *ast);
void			free_dbl_ptr(char **dbl_ptr);

/* debug.c */
void			print_tokens(t_token *head);
void			print_ast(t_ast *ast);
void			print_redir_list(t_redir *redir);

/* x_strdup.c */
char			*x_strdup(const char *to_dup);

#endif
