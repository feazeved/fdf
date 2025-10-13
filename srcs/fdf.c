/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feazeved <feazeved@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 15:20:52 by feazeved          #+#    #+#             */
/*   Updated: 2025/10/10 16:57:57 by feazeved         ###   ########.fr       */
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

void	ft_display_menu(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < 120)
	{
		j = 0;
		while (j < 200)
		{
			ft_mlx_pixel_put(data, j, i, GRAY);
			j++;
		}
		i++;
	}
}

void	ft_help_menu(t_data *data)
{
	int	i;
	int	j;

	if (!data->help_menu)
		return ;
	i = 140;
	while (i < 420)
	{
		j = 0;
		while (j < 200)
		{
			ft_mlx_pixel_put(data, j, i, GRAY);
			j++;
		}
		i++;
	}
	mlx_string_put(data->mlx, data->mlx_win, 10, 160, 0xFFFFFF, "W / S: Rotate on X axis");
	mlx_string_put(data->mlx, data->mlx_win, 10, 180, 0xFFFFFF, "A / D: Rotate on Y axis");
	mlx_string_put(data->mlx, data->mlx_win, 10, 200, 0xFFFFFF, "Q / E: Rotate on Z axis");
	mlx_string_put(data->mlx, data->mlx_win, 10, 240, 0xFFFFFF, "Arrow keys: Move");
	mlx_string_put(data->mlx, data->mlx_win, 10, 280, 0xFFFFFF, "Scroll: Zoom");
	mlx_string_put(data->mlx, data->mlx_win, 10, 300, 0xFFFFFF, "Plus and Minus: Zoom");
	mlx_string_put(data->mlx, data->mlx_win, 10, 340, 0xFFFFFF, "PgUp / PgDn: Change Z value");
	mlx_string_put(data->mlx, data->mlx_win, 10, 360, 0xFFFFFF, "R: Reset projection");
	mlx_string_put(data->mlx, data->mlx_win, 10, 400, 0xFFFFFF, "Esc: Exit program");
}

int	ft_render(t_data *data)
{
	ft_clear_image(data);
	update(data);
	ft_draw_map(data, 0, 1);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	ft_display_menu(data);
	ft_display_info(data);
	ft_help_menu(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	ft_memset(&data, 0, sizeof(t_data));
	ft_parsing(&data, argc, argv);
	ft_init_window(&data);
	ft_init_camera(&data);
	mlx_hook(data.mlx_win, 2, 1L << 0, key_press, &data);
	mlx_hook(data.mlx_win, 3, 1L << 1, key_release, &data);
	mlx_mouse_hook(data.mlx_win, mouse_hook, &data);
	mlx_loop_hook(data.mlx, ft_render, &data);
	mlx_hook(data.mlx_win, 17, 0, ft_close_window, &data);
	mlx_loop(data.mlx);
	ft_free_data(&data);
	return (0);
}
