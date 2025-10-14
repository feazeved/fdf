/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menus_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feazeved <feazeved@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 21:55:19 by feazeved          #+#    #+#             */
/*   Updated: 2025/10/13 21:55:39 by feazeved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	ft_display_menu(t_data *data, int first_y, int last_y, int last_x)
{
	int	i;
	int	j;

	i = first_y;
	while (i < last_y)
	{
		j = 0;
		while (j < last_x)
		{
			ft_mlx_pixel_put(data, j, i, GRAY);
			j++;
		}
		i++;
	}
}

void	ft_help_menu(t_data *data)
{
	if (!data->help_menu)
		return ;
	ft_display_menu(data, 140, 420, 200);
	mlx_string_put(data->mlx, data->mlx_win, 10, 160,
		0xFFFFFF, "W / S: Rotate on X axis");
	mlx_string_put(data->mlx, data->mlx_win, 10, 180,
		0xFFFFFF, "A / D: Rotate on Y axis");
	mlx_string_put(data->mlx, data->mlx_win, 10, 200,
		0xFFFFFF, "Q / E: Rotate on Z axis");
	mlx_string_put(data->mlx, data->mlx_win, 10, 220,
		0xFFFFFF, "Arrow keys: Move");
	mlx_string_put(data->mlx, data->mlx_win, 10, 260,
		0xFFFFFF, "> / <: Adjust rotation speed");
	mlx_string_put(data->mlx, data->mlx_win, 10, 280,
		0xFFFFFF, "Scroll: Zoom");
	mlx_string_put(data->mlx, data->mlx_win, 10, 300,
		0xFFFFFF, "Plus and Minus: Zoom");
	mlx_string_put(data->mlx, data->mlx_win, 10, 340,
		0xFFFFFF, "PgUp / PgDn: Change Z value");
	mlx_string_put(data->mlx, data->mlx_win, 10, 360,
		0xFFFFFF, "R: Reset projection");
	mlx_string_put(data->mlx, data->mlx_win, 10, 400,
		0xFFFFFF, "Esc: Exit program");
}

void	ft_display_info(t_data *data)
{
	char	*proj_str;
	char	*wu_str;

	ft_display_menu(data, 0, 120, 200);
	if (!data->camera.parallel)
		proj_str = "Isometric";
	else
		proj_str = "Parallel";
	if (data->wu_line)
		wu_str = "Xiaolin Wu (Smooth)";
	else
		wu_str = "Bresenham (Crisp)";
	mlx_string_put(data->mlx, data->mlx_win, 10, 20, 0xFFFFFF,
		"Projection: ");
	mlx_string_put(data->mlx, data->mlx_win, 120, 20, 0x00FF00, proj_str);
	mlx_string_put(data->mlx, data->mlx_win, 10, 40, 0xFFFFFF, "Lines: ");
	mlx_string_put(data->mlx, data->mlx_win, 80, 40, 0x00FF00, wu_str);
	mlx_string_put(data->mlx, data->mlx_win, 10, 60, 0xFFFFFF,
		"P: Toggle projection");
	mlx_string_put(data->mlx, data->mlx_win, 10, 80, 0xFFFFFF,
		"L: Toggle smooth lines");
	mlx_string_put(data->mlx, data->mlx_win, 10, 100, 0xFFFFFF, "H: Help menu");
}
