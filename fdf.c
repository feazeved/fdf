/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feazeved <feazeved@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 15:20:52 by feazeved          #+#    #+#             */
/*   Updated: 2025/09/20 20:45:30 by feazeved         ###   ########.fr       */
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

void ft_debug_data(t_data *data)
{
    printf("=== FDF DEBUG INFO ===\n");
    printf("Map dimensions: %dx%d (%d points)\n",
           data->map.width, data->map.height, data->map.np);
    printf("Z range: %d to %d\n", data->map.z_min, data->map.z_max);
    printf("Camera zoom: %d, angle: %f\n", data->camera.zoom, data->camera.angle);
    printf("Window size: %dx%d\n", data->w_width, data->w_height);

    printf("First 5 points:\n");
    for (int i = 0; i < 5 && i < data->map.np; i++)
    {
        printf("  Point %d: (%d, %d, %d)\n", i,
               data->map.points[i].x, data->map.points[i].y, data->map.points[i].z);
    }
    printf("======================\n");
}

int	ft_render(t_data *data)
{
	static int	first_render = 1;

	if (first_render)
	{
		ft_debug_data(data);
		first_render = 0;
	}
	ft_clear_image(data);
	ft_draw_fdf(data);
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

    printf("Map size: %dx%d, using zoom: %d\n",
           data->map.width, data->map.height, data->camera.zoom);
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

	mlx_key_hook(data.mlx_win, key_hook, &data);
	mlx_loop_hook(data.mlx, ft_render, &data);
	mlx_hook(data.mlx_win, 17, 0, ft_close_window, &data);
	mlx_loop(data.mlx);
	ft_free_data(&data);
	return (0);
}
