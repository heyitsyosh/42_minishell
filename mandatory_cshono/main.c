/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshono <cshono@student.42.tokyo>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 23:27:12 by myoshika          #+#    #+#             */
/*   Updated: 2022/12/12 23:52:12 by cshono           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	unset(char *id, m)
// {
	
// }

// execute_line(char *line, t_minishell *m)
// {
// 	unset(id, m->envp_head);
// }

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (i + 1 < dstsize && *(src + i))
	{
		*(dst + i) = *(src + i);
		i++;
	}
	if (dstsize != 0)
		*(dst + i) = '\0';
	return (ft_strlen(src));
}

size_t	ft_strnlen(const char *s, size_t maxlen)
{
	size_t	len;

	len = 0;
	while (maxlen-- && *(s + len) != '\0')
		len++;
	return (len);
}

char	*ft_strdup(const char *s1)
{
	char	*dup;

	dup = (char *)malloc(ft_strlen(s1) + 1);
	if (dup != NULL)
		ft_strlcpy(dup, s1, ft_strlen(s1) + 1);
	return (dup);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	sub_len;
	char	*sub;

	if (s == NULL)
		return (NULL);
	sub_len = ft_strnlen(s + start, len);
	if (*s == '\0' || sub_len == 0 || ft_strlen(s) <= start)
		return (ft_strdup(""));
	sub = (char *)malloc(sub_len + 1);
	if (sub == NULL)
		return (NULL);
	ft_strlcpy(sub, s + start, sub_len + 1);
	return (sub);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != (char)c)
		if (*s++ == '\0')
			return (NULL);
	return ((char *)s);
}


int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_minishell	m;
	

	init_shell(&m, envp);
	while (argc && argv)
	{
		//set_signal();
		line = readline("minishell>");
		if (!line)
			break ;
			// return (exit_minishell(m));
		if (*line != '\0')
			add_history(line);
		//execute_line(line, &m);
		free(line);
	}
	//exit();
}
