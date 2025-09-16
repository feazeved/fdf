/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feazeved <feazeved@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 21:23:16 by feazeved          #+#    #+#             */
/*   Updated: 2025/09/16 20:14:00 by feazeved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int	main(int argc, char *argv[])
{
	(void) argc;
	size_t length = 2147483648;
	char	*str = malloc(length + 1);

	if (!str)
		return (0);

	memset(str, 'a', length);
	str[length] = '\0';
	printf("mine: %zu\n", ft_strlen(str));
	printf("OG: %zu\n", strlen(str));
	return (0);
}*/
