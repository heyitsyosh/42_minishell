/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:07:51 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/19 05:53:09 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/expand.h"
#include <stdlib.h> //free

void	free_tokens(t_token *tok)
{
	t_token	*tmp;

	while (tok)
	{
		tmp = tok;
		tok = tok->next;
		free(tmp->word);
		free(tmp);
	}
}

void	free_sub_word_list(t_word *words)
{
	t_word	*tmp;

	while (words)
	{
		tmp = words;
		words = words->next;
		free(tmp->sub_word);
		free(tmp);
	}
}

void	free_envs(t_env *env)
{
	t_env	*node_to_free;

	while (env)
	{
		node_to_free = env;
		free(env->id);
		free(env->str);
		env = env->next;
		free(node_to_free);
	}
}

void	free_ast(t_ast *ast)
{
	if (ast)
	{
		free_ast(ast->left);
		free_ast(ast->right);
		if (ast->cmd)
		{
			free(ast->cmd->command);
			// if (ast->cmd->args)
				//free dbl ptr
			free_tokens(ast->cmd->arg_list);
		}
		free(ast);
	}
}
