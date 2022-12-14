/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshono <cshono@student.42.tokyo>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 21:11:04 by cshono            #+#    #+#             */
/*   Updated: 2022/12/14 15:54:21 by cshono           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	export(char *line, t_env *env)//line=exportするコマンド, env=リスト構造になっている環境変数
// {
// 	size_t i;
// 	char *str;
// 	t_env *tmp;

// 	i = 0;
// 	//pwd=chihiro
// 	tmp = make_node(line);
// 	if (!tmp)
// 		return ;
	
// 	//while (tmp->str != '\0')
	
// }

char	*check_export(char *str)//コマンド内の記号エラー確認
{
	size_t i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isalnum((str[i]))//コマンド内の記号エラー確認
		{
			printf("export: '%s': not a valid identifier\n",str);
			free(str);
			return (NULL);
		}
		i++;
		//if//コマンド内の空白(スペース)確認
	}
	return (str);
}

void	export(char *line, t_env *env)//pwd=chihiro, t_env
{
	size_t i;
	char *str;
	t_env *tmp;

	i = 0;
	if (!ft_isalpha(line[i]));//コマンドラインの先頭の文字が数字の場合のエラー処理。
		return;
	if (!ft_strchr(line, '='));//コマンドラインに0が含まれていなかった場合のエラー処理
		return;
	//tmp = get_env(line, get_env)
	str = (char *)malloc(sizeof(char)*ft_strlen(line));
	while (line[i] != '=')
	{
		str[i] = line[i];
		i++;
	}//mallocでメモリを確保する必要あり。
	str[i] = '\0';
	str = check_export(str);
	// tmp = get_env(str, env);//同じenvがあればその場所のポインタを返してくれる。
	// if(!tmp)//同じenvがなかった場合
	// 	node_add_back(env, tmp);
	//free(tmp);
}
