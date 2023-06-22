/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 01:58:27 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/23 08:21:30 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h> //printf, fflush

/*
void	print_tokens(t_token *head)
{
	while (head->next)
	{
		printf("%s->", head->word);
		head = head->next;
	}
	if (head)
		printf("%s\n", head->word);
}

static	void	print_ast_2(t_ast *ast)
{
	t_token	*tmp;

	if (!ast)
		return ;
	if (ast->type == CMD_NODE)
	{
		tmp = ast->cmd_list;
		printf(" [");
		while (tmp->next)
		{
			printf("%s->", tmp->word);
			tmp = tmp->next;
		}
		if (tmp)
			printf("%s]", tmp->word);
		fflush(stdout);
	}
	else if (ast->type == PIPE_NODE)
		printf("[|], ");
	else if (ast->type == AND_NODE)
		printf("[&&] ");
	else if (ast->type == OR_NODE)
		printf("[||] ");
	else if (ast->type == SUBSHELL_NODE)
		printf("[SUBSHELL] ");
}

void	print_ast(t_ast *ast)
{
	if (ast)
	{
		printf("current:%p", ast);
		print_ast_2(ast);
		printf(" left:%p ", ast->left);
		print_ast_2(ast->left);
		printf(", right:%p", ast->right);
		print_ast_2(ast->right);
		printf("\n");
		print_ast(ast->left);
		print_ast(ast->right);
	}
}
*/