/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 22:23:03 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/15 18:45:35 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <stddef.h> //size_t
# include <signal.h> //sig_atomic_t

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
	REDIR_APPEND,
	HEREDOC,
	REDIR_IN,
	REDIR_OUT,
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


	//t_redir			*redir;

typedef enum e_ast_node_type
{
	SUBSHELL_NODE,
	PIPE_NODE,
	AND_NODE,
	OR_NODE,
	CMD_NODE,
}	t_ast_node_type;

typedef struct s_cmd
{
	// t_redir	*redir;
	char	*command;
	char	**args;
}	t_cmd;

typedef struct s_ast_node
{
	t_ast_node_type		type;
	t_cmd				*cmd;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

typedef struct s_parse
{
	t_token	*tmp_args;
	char	*syntax_err_location;
}	t_parse;

//global struct//
typedef struct s_minishell{
	bool					is_interactive_mode;
	int						exit_status;
	char					*pwd;
	t_env					*envp_head;
	volatile sig_atomic_t	signum;
}	t_minishell;

extern t_minishell g_ms;

/* process_line.c */
void			run_commands(char *line);

/* init_envp.c */
void			init_envp(char **envp);

/* env_utils.c */
t_env			*get_env(char *var, t_env *env);
void			env_add_back(t_env *envp, t_env *new_node);
void			replace_env_str(t_env *env, char *new_str);
t_env			*make_env_node(char	*envp);
char			**env_list_to_dbl_ptr(void);

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

/* error.c */
void			print_error_and_exit(char *error_message);
void			print_syntax_error(char *unexpected_token);
void			msg_to_stderr(char *first, char *second, char *third);

/* free.c */
void			free_tokens(t_token *tok);
void			free_envs(t_env *env);

////////////////////////////////////////////////////////////////////
bool			is_valid_id(char *id);
/* BUILTINS */
// int				builtin_echo(t_token *args);
// int				builtin_unset(t_token *args);
// int				builtin_export(t_token *args);
// int				builtin_exit(t_token *args);
// int				builtin_cd(t_token *args);
// int				builtin_pwd(t_token *args);
// int				builtin_env(t_token *args);

// t_ast_node		*make_ast_node(t_token *token);
// void			attatch_ast_nodes(t_ast_node *base, \
// 				t_ast_node *left, t_ast_node *right);

// t_ast_node		*parser(t_token *tok);
// void	execute(t_node *node);
/////////////////////////////////////////////////////////

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

// typedef enum e_operator_type
// {
// 	AND_OPERATOR,
// 	OR_OPERATOR,
// 	NO_OPERATOR,
// }	t_operator_type;

// typedef struct s_commands{
// 	t_token				*args_list;
// 	t_operator_type		operator_type;
// 	struct s_commands	*next;
// }	t_commands;

/*typedef struct s_node
{
	t_type			type;
	t_token			*args;
	t_redir			*redir;
	struct s_node	*next;
}	t_node; */

#endif
