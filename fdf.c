/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feazeved <feazeved@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 15:20:52 by feazeved          #+#    #+#             */
/*   Updated: 2025/09/25 21:48:26 by feazeved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_test_parsing(t_map map)
{
	int	i;

	i = 0;
	printf("max z: %d\nmin z: %d\n\n", map.z_max, map.z_min);
	while (i < map.np)
	{
		printf("point: %d ", i);
		printf("x == %d   ", map.points[i].x);
		printf("y == %d   ", map.points[i].y);
		printf("z == %d\n", map.points[i].z);
		i++;
	}
}

void	ft_init_window(t_data *data)
{
	data->w_width = 1920;
	data->w_height = 1080;
	data->mlx = mlx_init();
	if (!data->mlx)
		ft_error(data, "Mlx_init", "could not initialize mlx");
	data->mlx_win = mlx_new_window(data->mlx, data->w_width, data->w_height,
			"FDF feazeved");
	if (!data->mlx_win)
		ft_error(data, "Mlx_new_window", "could not create a new window");
	data->img = mlx_new_image(data->mlx, data->w_width, data->w_height);
	if (!data->img)
		ft_error(data, "Mlx_new_image", "could not create a new image");
	data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->line_len,
			&data->endian);
	if (!data->addr)
		ft_error(data, "Mlx_get_data_addr", "could not get data addr");
}

void	ft_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (!data || !data->addr)
		return ;
	if (x < 0 || y < 0 || x >= data->w_width || y >= data->w_height)
		return ;
	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void	ft_clear_image(t_data *data)
{
	if (!data || !data->addr)
		return ;
	ft_memset(data->addr, 0, data->w_height * data->line_len);
}

void	ft_drawline(t_data *data, t_point a, t_point b)
{
	float	delta_x;
	float	delta_y;
	float	m;
	int		i;
	float	x;
	float	y;

	if (ft_abs(b.screen_y - a.screen_y) < ft_abs(b.screen_x - a.screen_x))
	{
		if (b.screen_x < a.screen_x)
		{
			i = a.screen_x;
			a.screen_x = b.screen_x;
			b.screen_x = i;
	
			i = a.screen_y;
			a.screen_y = b.screen_y;
			b.screen_y = i;
		}
		b.screen_x += (data->w_width / 2);
		b.screen_y += (data->w_height / 2);
		a.screen_x += (data->w_width / 2);
		a.screen_y += (data->w_height / 2);
		delta_x = b.screen_x - a.screen_x;
		delta_y = b.screen_y - a.screen_y;
		if (delta_x == 0)
			m = 1;
		else
			m = delta_y / delta_x;
		i = 0;
		while (i < delta_x + 1)
		{
			x = a.screen_x + i;
			y = a.screen_y + i * m;
			i++;
			ft_mlx_pixel_put(data, x, y, 0xFFFFFF);
			ft_mlx_pixel_put(data, x, y + 1, 0xFFFFFF);
		}
	}
	else
	{
		if (b.screen_y < a.screen_y)
		{
			i = a.screen_x;
			a.screen_x = b.screen_x;
			b.screen_x = i;

			i = a.screen_y;
			a.screen_y = b.screen_y;
			b.screen_y = i;
		}
		b.screen_x += (data->w_width / 2);
		b.screen_y += (data->w_height / 2);
		a.screen_x += (data->w_width / 2);
		a.screen_y += (data->w_height / 2);
		delta_x = b.screen_x - a.screen_x;
		delta_y = b.screen_y - a.screen_y;
		if (delta_y == 0)
			m = 1;
		else
			m = delta_x / delta_y;
		i = 0;
		while(i < delta_y + 1)
		{
			x = a.screen_x + i * m;
			y = a.screen_y + i;
			i++;
			ft_mlx_pixel_put(data, x, y, 0xFFFFFF);
			ft_mlx_pixel_put(data, x, y, 0xFFFFFF);
		}
	}
}

void	ft_project(t_point *point)
{
	point->screen_x = (int)(((point->x * 50) - (point->y * 50)) * cos(0.523599));
	point->screen_y = (int)(((point->x * 50) + (point->y * 50)) * sin(0.523599) - (point->z * 4));
}

void	ft_draw(t_data *data)
{
	int	x;
	int	y;
	int	i;
	int	p;

	i = 0;
	y = 0;
	while (i < data->map.np)
	{
		x = 0;
		while (x < data->map.width)
		{
			p = (y * data->map.width + x);
			ft_project(&data->map.points[p]);
			if (data->map.points[p].x != data->map.points[data->map.np - 1].x)
				ft_drawline(data, data->map.points[p], data->map.points[p + 1]);
			if (data->map.points[p].y != data->map.points[data->map.np - 1].y)
				ft_drawline(data, data->map.points[p], data->map.points[p + data->map.width]);
			x++;
			i++;
		}
		y++;
	}
}

int	ft_render(t_data *data)
{
	ft_clear_image(data);
	ft_draw(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	return (0);
}

void	ft_init_camera(t_data *data)
{
	int	max_dimension;

	if (data->map.width > data->map.height)
		max_dimension = data->map.width;
	else
		max_dimension = data->map.height;
	data->camera.scale = 1.0;
	data->camera.angle = 0.5236;
	data->camera.zoom = 25;
	if (max_dimension <= 10)
        data->camera.zoom = 50;
    else if (max_dimension <= 20)
        data->camera.zoom = 25;
    else if (max_dimension <= 50)
        data->camera.zoom = 15;
    else if (max_dimension <= 100)
        data->camera.zoom = 8;
    else
        data->camera.zoom = 4;
}

int	ft_close_window(t_data *data)
{
	ft_free_data(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	ft_memset(&data, 0, sizeof(t_data));
	ft_parsing(&data, argc, argv);
	ft_init_window(&data);
	ft_init_camera(&data);

	ft_test_parsing(data.map);

	mlx_key_hook(data.mlx_win, key_hook, &data);
	mlx_loop_hook(data.mlx, ft_render, &data);
	mlx_hook(data.mlx_win, 17, 0, ft_close_window, &data);
	mlx_loop(data.mlx);
	ft_free_data(&data);
	return (0);
}