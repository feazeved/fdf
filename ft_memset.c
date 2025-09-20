/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feazeved <feazeved@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 20:57:05 by feazeved          #+#    #+#             */
/*   Updated: 2025/09/20 20:11:10 by feazeved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*temp;

	i = 0;
	temp = s;
	while (i < n)
	{
		temp[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
/*
#include <string.h>
int	main(void)
{
	char	f[50] = "abcdefghijklmnopqrstuvwxyz";
	printf("beginning: %s\n", f);
	printf("og ft: %s\n", (char *)memset(f, 65, 20));
	printf("my ft: %s\n", (char *)ft_memset(f, 65, 20));
	return (0);
}*/
