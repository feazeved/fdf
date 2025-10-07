/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feazeved <feazeved@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 15:20:52 by feazeved          #+#    #+#             */
/*   Updated: 2025/10/07 20:05:39 by feazeved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

int	ft_render(t_data *data)
{
	ft_clear_image(data);
	ft_draw_map(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	return (0);
}

void	ft_init_camera(t_data *data)
{
	int	max_dimension;

	max_dimension = data->map.width;
	if (data->map.height > max_dimension)
		max_dimension = data->map.height;
	data->camera.scale = 1.0;
	data->camera.angle_x = 0.0;
	data->camera.angle_y = 0.0;
	data->camera.angle_z = 0.523599;
	data->camera.offset_x = 0;
	data->camera.offset_y = 0;
	data->camera.z_scale = 0.25;
	if (max_dimension <= 10)
        data->camera.zoom = 50;
    else if (max_dimension <= 20)
        data->camera.zoom = 25;
    else if (max_dimension <= 50)
        data->camera.zoom = 15;
    else if (max_dimension <= 100)
        data->camera.zoom = 8;
    else if (max_dimension <= 200)
        data->camera.zoom = 4;
	else if (max_dimension <= 400)
		data->camera.zoom = 2;
	else
		data->camera.zoom = 1;
}

void	ft_reset_camera(t_data *data)
{
	data->camera.angle_x = 0.0;
	data->camera.angle_y = 0.0;
	data->camera.angle_z = 0.523599;
	data->camera.offset_x = 0;
	data->camera.offset_y = 0;
	data->camera.z_scale = 2.5;
	ft_init_camera(data);
}

int	ft_close_window(t_data *data)
{
	ft_free_data(data);
	return (0);
}
void	test_color_parsing(char *input)
{
	char	*str = input;
	char	*color_start;
	int		z_value = 0;
	int		color = -1;
	int		sign = 1;
	
	printf("\n=== Testing: '%s' ===\n", input);
	
	// Find comma
	color_start = str;
	while (*color_start && *color_start != ',')
		color_start++;
	
	// Parse Z
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		z_value = z_value * 10 + (*str - '0');
		str++;
	}
	z_value *= sign;
	
	// Parse color
	if (*color_start == ',')
	{
		color_start++;
		if (*color_start == '0' && *(color_start + 1) == 'x')
		{
			color_start += 2;
			color = ft_ahextoint(color_start);
		}
	}
	
	printf("Z value: %d\n", z_value);
	printf("Color (hex): 0x%06X\n", color);
	printf("Color (RGB): R=%d, G=%d, B=%d\n",
		(color >> 16) & 0xFF,
		(color >> 8) & 0xFF,
		color & 0xFF);
}
int	main(int argc, char **argv)
{
	t_data	data;

	ft_memset(&data, 0, sizeof(t_data));
	ft_parsing(&data, argc, argv);
	ft_init_window(&data);
	ft_init_camera(&data);
	mlx_key_hook(data.mlx_win, key_hook, &data);
	mlx_mouse_hook(data.mlx_win, mouse_hook, &data);
	mlx_loop_hook(data.mlx, ft_render, &data);
	mlx_hook(data.mlx_win, 17, 0, ft_close_window, &data);
	mlx_loop(data.mlx);
	ft_free_data(&data);
	return (0);
}
