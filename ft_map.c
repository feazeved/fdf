/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feazeved <feazeved@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 19:08:14 by feazeved          #+#    #+#             */
/*   Updated: 2025/09/16 23:30:34 by feazeved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_error(t_data *data, char *func, char *msg)
{
	if (data)
		ft_free_data(data);
	if (func)
	{
		write(2, func, ft_strlen(func));
		write(2, ": ", 2);
	}
	if (msg)
		write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	exit(69);
}

void	ft_free_data(t_data *data)
{
	if (data->map.points)
		free(data->map.points);
	if (data->line)
		free(data->line);
	if (data->split)
		ft_free_strs(data->split);
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

void	ft_parsing(t_data *data, int argc, char **argv)
{
	if (argc != 2)
	{
		ft_error(NULL, "Invalid input, you should do", "./fdf map");
	}
	data->line = NULL;
	data->split = NULL;
	ft_set_map_size(data, argv);
	ft_set_numbers(0, data, argv);
}

void	ft_set_point(t_point *point, int y, int x, char *str)
{
	int	sign;
	int	num;

	sign = 1;
	num = 0;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		num = (*str - '0') + (num * 10);
		str++;
	}
	point->z = num * sign;
	point->x = x;
	point->y = y;
	if (!(*str))
		return ;
}

void	ft_set_numbers(int y, t_data *data, char **argv)
{
	int		x;
	int		fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_error(data, "Open", strerror(errno));
	data->map.points = ft_fdf_calloc(data->map.np, sizeof(t_point), data);
	while (y < data->map.height)
	{
		x = 0;
		data->line = get_next_line(fd);
		data->split = ft_split(data->line, ' ');
		if (!data->split || !data->line)
			ft_error(data, "Malloc", strerror(errno));
		while (x < data->map.width)
		{
			ft_set_point(&data->map.points[y * data->map.width + x], y, x, data->split[x]);
			x++;
		}
		free(data->line);
		data->line = NULL;
		ft_free_strs(data->split);
		data->split = NULL;
		y++;
	}
}

void	*ft_fdf_calloc(int nmemb, size_t size, t_data *data)
{
	unsigned char	*str;
	size_t			i;
	size_t			sum;

	i = 0;
	sum = nmemb * size;
	str = malloc(sum);
	if (!data)
		ft_error(data, "Malloc", strerror(errno));
	while (i < sum)
	{
		str[i] = 0;
		i++;
	}
	return (str);
}

int	ft_count_words(char *str, char sep)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (str && str[i])
	{
		while (str[i] == sep)
			i++;
		if (str[i])
			words++;
		while (str[i] && str[i] != sep)
			i++;
	}
	return (words);
}

void	ft_set_map_size(t_data *data, char **argv)
{
	int		height;
	int		fd;
	char	*line;
	int		width;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_error(data, "Open", strerror(errno));
	height = 0;
	width = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!width)
			width = ft_count_words(line, ' ');
		free(line);
		height++;
	}
	data->map.height = height;
	data->map.width = width;
	data->map.np = data->map.height * data->map.width;
	close(fd);
}
/*
char *onde_esta_o_afonso(time_t now)
{
	(void) now;
	return ("a fumar");
}*/
