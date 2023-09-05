/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:07:51 by myoshika          #+#    #+#             */
/*   Updated: 2023/09/05 22:27:12 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h> //free

void	free_tokens(t_token *tok)
{
	t_token	*tok_to_free;

	while (tok)
	{
		tok_to_free = tok;
		tok = tok->next;
		free(tok_to_free->word);
		free(tok_to_free);
	}
}

void	free_envs(t_env *env)
{
	t_env	*node_to_free;

	while (env)
	{
		node_to_free = env;
		env = env->next;
		free(env->id);
		free(env->str);
		free(node_to_free);
	}
}

static void	free_redir(t_redir *redir)
{
	t_redir	*redir_to_free;

	if (!redir)
		return ;
	while (redir)
	{
		redir_to_free = redir;
		redir = redir->next;
		free(redir->delimiter);
		free(redir->filename);
		free(redir_to_free);
	}
}

void	free_ast(t_ast *ast)
{
	if (ast)
	{
		free_ast(ast->left);
		free_ast(ast->right);
		free_redir(ast->redir);
		free_tokens(ast->cmd_list);
		free(ast);
	}
}

void	free_dbl_ptr(char **dbl_ptr)
{
	size_t	i;

	i = 0;
	if (!dbl_ptr)
		return ;
	while (dbl_ptr[i])
	{
		free(dbl_ptr[i]);
		i++;
	}
	free(dbl_ptr);
}
