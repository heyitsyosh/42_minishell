/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 01:58:27 by myoshika          #+#    #+#             */
/*   Updated: 2023/08/22 23:43:46 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h> //printf, fflush

void	print_tokens(t_token *head)
{
	while (head->next)
	{
		printf("[%s]->", head->word);
		head = head->next;
	}
	if (head)
		printf("[%s]\n", head->word);
}

void	print_redir_list(t_redir *redir)
{
	printf("[REDIR: ");
	while (redir)
	{
		if (redir->filename)
			printf("filename:%s ", redir->filename);
		if (redir->delimiter)
			printf("delimiter:%s ", redir->delimiter);
		printf("target_fd:%d", redir->target_fd);
		redir = redir->next;
		if (redir)
			printf("->");
	}
	printf("]");
}

static void	print_cmd_list(t_token *cmd_list)
{
	if (!cmd_list)
		return ;
	printf("[");
	while (cmd_list->next)
	{
		printf("%s->", cmd_list->word);
		cmd_list = cmd_list->next;
	}
	if (cmd_list)
		printf("%s], ", cmd_list->word);
}

static void	print_ast_2(t_ast *ast)
{
	if (!ast)
		return ;
	if (ast->type == CMD_NODE)
		print_cmd_list(ast->cmd_list);
	else
	{
		if (ast->type == PIPE_NODE)
			printf(" [|], ");
		else if (ast->type == AND_NODE)
			printf(" [&&], ");
		else if (ast->type == OR_NODE)
			printf(" [||], ");
		else if (ast->type == SUBSHELL_NODE)
			printf(" [SUBSHELL] ");
	}
	if (ast->redir)
		print_redir_list(ast->redir);
}

void	print_ast(t_ast *ast)
{
	if (ast)
	{
		printf("current:%p ", ast);
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
