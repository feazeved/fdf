/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feazeved <feazeved@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 20:48:02 by feazeved          #+#    #+#             */
/*   Updated: 2025/10/09 18:52:01 by feazeved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_parsing(t_data *data, int argc, char **argv)
{
	if (argc != 2)
	{
		ft_error(NULL, "Invalid input, you should do", "./fdf map");
	}
	data->fd = -1;
	ft_check_map(data, argv);
	ft_set_map_size(data, argv);
	ft_set_numbers(0, data, argv);
	ft_set_z_limits(data);
	ft_center_points(data);
	ft_assign_colors(data);
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
	data->fd = fd;
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

void	ft_set_numbers(int y, t_data *data, char **argv)
{
	int		x;
	int		fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_error(data, "Open", strerror(errno));
	data->fd = fd;
	data->map.points = ft_fdf_calloc(data->map.np, sizeof(t_point), data);
	while (y < data->map.height)
	{
		x = -1;
		data->line = get_next_line(fd);
		data->split = ft_split(data->line, ' ');
		if (!data->split || !data->line)
			ft_error(data, "Malloc", strerror(errno));
		while (++x < data->map.width)
			ft_set_point(&data->map.points[y * data->map.width + x],
				y, x, data->split[x]);
		free(data->line);
		data->line = NULL;
		ft_free_strs(data->split);
		data->split = NULL;
		y++;
	}
}

void	ft_set_point(t_point *point, int y, int x, char *str)
{
	int	sign;
	int	num;

	sign = 1;
	num = 0;
	point->color = -1;
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
	if (*str == ',')
		point->color = ft_parse_color(&str);
}

int	ft_parse_color(char **str)
{
	int	color;

	color = 0;
	while (**str && **str != ',')
		(*str)++;
	if (**str == ',')
	{
		(*str)++;
		if (**str == '0' && *(*str + 1) == 'x')
		{
			*str += 2;
			color = ft_ahextoint(*str);
		}
	}
	return (color);
}
