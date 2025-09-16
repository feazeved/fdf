/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feazeved <feazeved@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 04:01:40 by feazeved          #+#    #+#             */
/*   Updated: 2025/09/16 19:48:56 by feazeved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_strlen_line(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	return (i);
}

static int	ft_clean_buffer(char *buffer)
{
	int	br;
	int	i;
	int	j;

	i = 0;
	j = 0;
	br = 0;
	while (buffer[i])
	{
		if (br == 1)
			buffer[j++] = buffer[i];
		if (buffer[i] == '\n')
			br = 1;
		buffer[i++] = '\0';
	}
	while (j < i)
		buffer[j++] = '\0';
	return (br);
}

static char	*ft_str_join_and_free(char *old, char *buffer)
{
	char	*new;
	int		i;
	int		j;

	new = malloc((ft_strlen_line(old) + ft_strlen_line(buffer) + 1));
	if (!new)
		return (free(old), NULL);
	i = 0;
	while (old && old[i])
	{
		new[i] = old[i];
		i++;
	}
	j = 0;
	while (buffer && buffer[j])
	{
		new[i++] = buffer[j];
		if (buffer[j] == '\n')
			break ;
		j++;
	}
	new[i] = '\0';
	return (free(old), new);
}

static void	ft_initializer(char **line, int *br, int *num_read)
{
	*br = 0;
	*line = NULL;
	*num_read = 1;
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	int			br;
	int			num_read;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	ft_initializer(&line, &br, &num_read);
	while (!br)
	{
		if (!buffer[0])
		{
			num_read = read(fd, buffer, BUFFER_SIZE);
			if (num_read == -1)
				return (free(line), NULL);
			if (num_read == 0)
				break ;
		}
		line = ft_str_join_and_free(line, buffer);
		if (!line)
			return (NULL);
		br = ft_clean_buffer(buffer);
	}
	return (line);
}
