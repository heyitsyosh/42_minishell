/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 22:23:03 by myoshika          #+#    #+#             */
/*   Updated: 2023/09/06 04:17:53 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <stddef.h> //size_t
# include <signal.h> //sig_atomic_t
# include <sys/types.h> //pid_t

# define NOT_IN_DQUOTE 0
# define IN_DQUOTE 1

# define IS_PARENT 0
# define IS_CHILD 1

# define NO_PIPE 0
# define BESIDE_PIPE 1

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

typedef struct s_redir
{
	char			*filename;
	int				file_fd;
	int				target_fd;
	int				stashed_target_fd;
	bool			io_num_used;
	int				io_num;
	char			*delimiter;
	t_token_type	type;
	struct s_redir	*prev;
	struct s_redir	*next;
}	t_redir;

typedef enum e_ast_node_type
{
	SUBSHELL_NODE,
	PIPE_NODE,
	AND_NODE,
	OR_NODE,
	CMD_NODE,
}	t_ast_node_type;

typedef struct s_ast
{
	t_ast_node_type	type;
	t_token			*cmd_list;
	t_redir			*redir;
	int				pipe_status;
	int				input_fd;
	pid_t			pid;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

typedef enum e_sub_word_type
{
	QUOTED,
	DQUOTED,
	UNQUOTED,
	WILDCARD,
	HEAD,
}	t_sub_word_type;

typedef struct s_word
{
	char			*sub_word;
	t_sub_word_type	type;
	struct s_word	*next;
}	t_word;

typedef struct s_env{
	char			*id;
	char			*str;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_pipeline{
	t_ast				*pipe_elem;
	struct s_pipeline	*next;
}	t_pipeline;

typedef struct s_data{
	int						exit_status;
	char					*pwd;
	char					*shlvl;
	t_env					*envp;
}	t_data;

/* init_envp.c */
void			init_envp(char **envp, t_data *d);

/* signal.c */
void			signal_handler(int signal);
void			setup_child_signal_handler(void);
void			setup_parent_signal_handler(void);

/* tokenize.c */
t_token			*tokenize(char *line);

/* tokenize_utils.c */
bool			is_blank(char c);
bool			is_operator(char c);
bool			is_io_number(char *line);
t_token_type	get_operator_type(char *operator);
t_token			*make_token(char *word, t_token_type type);

/* expand.c */
void			expand(t_token *tok, t_data *d);

/* word_to_list.c */
t_word			*divide_word_to_list(char *word, t_data *d);

/* word_to_list_ii.c */
char			*get_quoted_str(char *quote, size_t *i);
char			*get_dquoted_str(char *dquote, size_t *i, t_data *d);
char			*get_unquoted_str(char *no_quote, size_t *i, t_data *d);

/* variable_expansion.c */
char			*variable_expansion(char *ptr, size_t *i_mover, t_data *d);

/* wildcard_expansion.c */
t_token			*wildcard_expansion(t_word *word, t_token *next);

/* word_to_list_util.c */
t_word			*make_sub_word(char *sub_word, t_sub_word_type type);
t_word			*ret_word_head(t_word *list_head);
size_t			no_interpretation_len(char *ptr, int status);
void			free_sub_word_list(t_word *words);

/* parse.c */
t_ast			*parser(t_token *tok);
t_ast			*create_ast(t_token **tok, char **syntax_err);
t_ast			*parse_pipe(t_token **tok, char **syntax_err);
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

/* exec.c */
void			execute(t_ast *ast, t_data *d);
void			execute_cmd(t_ast *cmd, t_data *d);
void			execute_subshell(t_ast *ast, t_data *d);

/* exec_builtin.c */
bool			is_builtin(char *cmd);
void			exec_builtin(t_token *cmd_list, t_data *d);

/* exec_nonbuiltin.c */
void			exec_nonbuiltin(t_token *cmd_list, t_data *d);

/* exec_pipeline.c */
void			execute_pipeline(t_ast *ast, t_data *d);

/* pipeline_io.c */
void			save_io(int saved_io[2]);
void			set_pipe(int input_fd, int fd[2]);
void			restore_io(int saved_io[2]);

/* pipeline_list.c */
void			flatten_ast(t_ast *pipe_elem, t_pipeline **pipeline);
void			free_pipeline_list(t_pipeline *pipeline);

/* wait.c */
void			wait_one_child(pid_t pid, t_data *d);
void			wait_all_children(t_pipeline *pipeline, t_data *d);

/* redirect.c */
bool			open_redir_files(t_redir *redir, bool process_type, t_data *d);
void			set_up_redirect(t_redir *redir);
void			reset_redirect(t_redir *redir);

/* heredoc.c */
int				set_up_heredoc(t_redir *redir, t_data *d);

/* make_argv.c */
char			**make_argv_from_list(t_token *cmd_list);

/* make_envp.c */
char			**make_envp_from_list(t_data *d);

/* builtins.c */
int				builtin_echo(t_token *args, t_data *d);
int				builtin_cd(t_token *args, t_data *d);
int				builtin_pwd(t_token *args, t_data *d);
int				builtin_export(t_token *args, t_data *d);
int				builtin_unset(t_token *args, t_data *d);
int				builtin_env(t_token *args, t_data *d);
int				builtin_exit(t_token *args, t_data *d);

bool			is_valid_id(char *id);
void			update_pwd(char *chdir_path, t_data *d);

/* env_utils.c */
t_env			*get_env(char *var, t_env *envp);
void			add_new_env(t_env *tmp, t_data *d);
void			env_add_back(t_env *envp, t_env *new_node);
void			replace_env_str(t_env *env, char *new_str);
t_env			*make_env_node(char	*envp);

/* error.c */
void			print_error_and_exit(char *error_message);
void			print_syntax_error(char *unexpected_token);

/* free.c */
void			free_tokens(t_token *tok);
void			free_envs(t_env *env);
void			free_ast(t_ast *ast);
void			free_dbl_ptr(char **dbl_ptr);

/* debug.c */
void			print_tokens(t_token *head);
void			print_ast(t_ast *ast);
void			print_redir_list(t_redir *redir);
void			print_cmd_list(t_token *cmd_list);

/* wrappers */
int				x_close(int fd);
int				x_dup(int oldfd);
int				x_dup2(int oldfd, int newfd);
pid_t			x_fork(void);
char			*x_strdup(const char *to_dup);
char			*x_strjoin_free(char *s1, char *s2, int to_free);

#endif
