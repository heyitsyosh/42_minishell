/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 21:11:04 by cshono            #+#    #+#             */
/*   Updated: 2022/12/19 18:57:21 by myoshika         ###   ########.fr       */
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

// char	*check_export(char *str)//コマンド内の記号エラー確認
// {
// 	size_t i;

// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		if (!ft_isalnum((str[i]))//コマンド内の記号エラー確認
// 		{
// 			printf("export: '%s': not a valid identifier\n",str);
// 			free(str);
// 			return (NULL);
// 		}
// 		i++;
// 		//if//コマンド内の空白(スペース)確認
// 	}
// 	return (str);
// }

char    *ft_strtok(char *str, char sepa)
{
    static char *stock = NULL;
    char        *ptr;
    int     i;

    i = 0;
    ptr = NULL;
    if (str != NULL)
        stock = ft_strdup(str);
    while (*stock != '\0')
    {
        if (i == 0 && *stock != sepa)
        {
            i = 1;
            ptr = stock;
        }
        else if (i == 1 && *stock == sepa)
        {
            *stock = '\0';
            stock += 1;
            break ;
        }
        stock++;
    }
    return (ptr);
}

void	export(char *line, t_env *env)//pwd=chihiro, t_env
{
	size_t i;
	char *str;
	t_env *tmp;

	tmp = NULL;
	i = 0;
	if (!ft_isalpha(line[i]));//コマンドラインの先頭の文字が数字の場合のエラー処理。
		return;
	if (!ft_strchr(line, '='));//コマンドラインに=が含まれていなかった場合のエラー処理
		return;
	str = ft_strtok(line, '=');
	tmp = get_env(str, get_env);//あればそこのアドレスが返ってくる。NULLだと
	if(!tmp)
	{
		tmp->var = str;
		node_add_back(env,tmp);
	}
	if (tmp)
	{
		tmp->str = str;
	}
	free(str);
}
