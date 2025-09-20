/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aditional_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feazeved <feazeved@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 19:36:48 by feazeved          #+#    #+#             */
/*   Updated: 2025/09/20 20:47:13 by feazeved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point ft_project(t_point point, t_data *data)
{
	t_point	projected;
	double	angle;
	double	x;
	double	y;
	double	z;

	angle = data->camera.angle;
	x = (double)point.x * data->camera.zoom;
	y = (double)point.y * data->camera.zoom;
	z = (double)point.z * data->camera.zoom * 0.5;
	projected.x = (int)((x - y) * cos(angle));
	projected.y = (int)((x + y) * sin(angle) - z);
	projected.x += data->w_width / 2;
	projected.y += data->w_height / 2;
	projected.z = 0;
	return (projected);
}

void	ft_draw_line(t_data *data, t_point p0, t_point p1, int color)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;
	int	steps;
	int	max_steps;

	if (ft_abs(p0.x) > 5000 || ft_abs(p0.y) > 5000 || ft_abs(p1.x) > 5000 || ft_abs(p1.y > 5000))
		return ;
	dx = ft_abs(p1.x - p0.x);
	dy = ft_abs(p1.y - p0.y);
	err = dx - dy;
	if (p0.x < p1.x)
		sx = 1;
	else
		sx = -1;
	if (p0.y < p1.y)
		sy = 1;
	else
		sy = -1;
	steps = 0;
	max_steps = dx + dy + 1000;
	while (steps < max_steps)
	{
		if (p0.x >= 0 && p0.x < data->w_width && p0.y >= 0 && p0.y < data->w_height)
			ft_mlx_pixel_put(data, p0.x, p0.y, color);
		if (p0.x == p1.x && p0.y == p1.y)
			break ;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			p0.x += dx;
		}
		if (e2 < dx)
		{
			err += dx;
			p0.y += sy;
		}
		steps++;
	}
}

int	ft_get_color(int z, t_data *data)
{
	if (data->map.z_max == data->map.z_min)
		return (0xFFFFFF);
	if (z == 0)
		return (0x00FF00);
	else if (z > 0)
		return (0xFF0000);
	else
		return (0x0000FF);
}

void	ft_draw_fdf(t_data *data)
{
	int		i;
	int		j;
	t_point	current;
	t_point	right;
	t_point	down;
	int	color;

	i = 0;
	printf("Drawing wireframe: %dX%d point\n", data->map.width, data->map.height);
	while (i < data->map.height)
	{
		j = 0;
		while (j < data->map.width)
		{
			current = ft_project(data->map.points[i * data->map.width + j], data);
			color = ft_get_color(data->map.points[i * data->map.width + j].z, data);
			if (j < data->map.width - 1)
			{
				right = ft_project (data->map.points[i * data->map.width + j + 1], data);
				ft_draw_line(data, current, right, color);
			}
			if (i < data->map.height - 1)
			{
				down = ft_project(data->map.points[(i + 1) * data->map.width + j], data);
				ft_draw_line(data, current, down, color);
			}
			j++;
		}
		i++;
	}
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == 65307)
	{
		ft_free_data(data);
		exit(0);
	}
	if (keycode == 61 || keycode == 65451)
	{
		data->camera.zoom += 5;
		if (data->camera.zoom > 100)
			data->camera.zoom = 100;
	}
	if (keycode == 45 || keycode == 65453)
	{
		data->camera.zoom -= 5;
		if (data->camera.zoom < 1)
			data->camera.zoom = 1;
	}
	if (keycode == 113)
	{
		data->camera.angle -= 0.1;
		if (data->camera.angle < 0)
			data->camera.angle = 0;
	}
	if (keycode == 101)
	{
		data->camera.angle += 0.1;
		if (data->camera.angle > 1.5708)
			data->camera.angle = 15708;
	}
	if (keycode == 114)
	{
		data->camera.zoom = 25;
		data->camera.angle = 0.5236;
	}
	return (0);
}
