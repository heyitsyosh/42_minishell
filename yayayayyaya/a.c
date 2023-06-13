/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 21:45:42 by myoshika          #+#    #+#             */
/*   Updated: 2023/06/10 10:46:22 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "../includes/libft.h"
#include <stdint.h> //SIZE_MAX

// int main(int argc, char **argv)
// {
// 	char *endptr;
// 	char *input;

// 	input = "0x";
// 	ft_strtol(input, &endptr, 10);
// 	printf("[input: %s][endptr: %c]\n", input, *endptr);
// 	input = "0x3a";
// 	ft_strtol(input, &endptr, 10);
// 	printf("[input: %s][endptr: %c]\n", input, *endptr);
// }

// sample.c
#include <stdio.h>

int main(int argc, char *argv[])
{
	for (int i = 0; i < argc; i++) {
		printf("argv[%d] = [%s]\n", i, argv[i]);
	}
}