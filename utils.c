/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
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

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t			i;
	size_t			a;
	unsigned char	*ptr;

	i = 0;
	a = nmemb * size;
	if (size && (a / size != nmemb))
		return (NULL);
	ptr = malloc(a);
	if (!ptr)
		return (NULL);
	while (i < a)
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}

int	ft_abs(int n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}

void	ft_free_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs && strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
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
