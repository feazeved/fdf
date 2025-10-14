/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_algorithm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feazeved <feazeved@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 20:36:54 by feazeved          #+#    #+#             */
/*   Updated: 2025/10/09 19:38:21 by feazeved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_draw_map(t_data *data, int y, int skip)
{
	int	x;
	int	p;

	if (data->map.width >= 200 || data->map.height >= 200)
		skip = 2;
	if (data->map.width > 400 || data->map.height > 400)
		skip = 3;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			p = y * data->map.width + x;
			ft_project(&data->map.points[p], &data->camera);
			if (x < data->map.width - skip)
				ft_drawline(data, data->map.points[p],
					data->map.points[p + skip]);
			if (y < data->map.height - skip)
				ft_drawline(data, data->map.points[p],
					data->map.points[p + (skip * data->map.width)]);
			x += skip;
		}
		y += skip;
	}
}

void	ft_drawline(t_data *data, t_point a, t_point b)
{
	a.screen_x += data->w_width / 2;
	a.screen_y += data->w_height / 2;
	b.screen_x += data->w_width / 2;
	b.screen_y += data->w_height / 2;
	if (abs(b.screen_x - a.screen_x) > abs(b.screen_y - a.screen_y))
		ft_draw_horizontal(data, a, b);
	else
		ft_draw_vertical(data, a, b);
}

void	ft_draw_vertical(t_data *data, t_point a, t_point b)
{
	int		delta[2];
	float	slope;
	int		step[2];
	int		i;
	int		color;

	ft_init_line(&a, &b, delta, &slope);
	if (b.screen_x >= a.screen_x)
		step[0] = 1;
	else
		step[0] = -1;
	if (b.screen_y >= a.screen_y)
		step[1] = 1;
	else
		step[1] = -1;
	i = 0;
	while (i <= delta[1])
	{
		color = ft_interpolate_color(a.color, b.color, (float)i / delta[1]);
		ft_mlx_pixel_put(data, a.screen_x + (int)(i
				* slope * step[0]), a.screen_y + i * step[1], color);
		i++;
	}
}

void	ft_draw_horizontal(t_data *data, t_point a, t_point b)
{
	int		delta[2];
	float	slope;
	int		step[2];
	int		i;
	int		color;

	ft_init_line(&a, &b, delta, &slope);
	if (b.screen_x >= a.screen_x)
		step[0] = 1;
	else
		step[0] = -1;
	if (b.screen_y >= a.screen_y)
		step[1] = 1;
	else
		step[1] = -1;
	i = 0;
	while (i <= delta[0])
	{
		color = ft_interpolate_color(a.color, b.color,
				(float)i / delta[0]);
		ft_mlx_pixel_put(data, a.screen_x + i * step[0],
			a.screen_y + (int)(i * slope * step[1]), color);
		i++;
	}
}
