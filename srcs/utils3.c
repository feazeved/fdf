/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feazeved <feazeved@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 16:18:55 by feazeved          #+#    #+#             */
/*   Updated: 2025/10/09 18:52:12 by feazeved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_close_window(t_data *data)
{
	ft_free_data(data);
	return (0);
}

void	ft_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (!data || !data->addr || (x < 2 || y < 2))
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

void	ft_display_info(t_data *data)
{
	char	*proj_str;
	char	*wu_str;

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

void	ft_check_map(t_data *data, char **argv)
{
	int	i;

	i = 0;
	while (argv[1][i])
		i++;
	if (i > 4)
	{
		i -= 4;
		if (argv[1][i] != '.' || argv[1][i + 1] != 'f' || argv[1][i + 2] != 'd'
			|| argv[1][i + 3] != 'f')
			ft_error(data, "File", "use a valid map");
	}
	else
		ft_error(data, "File", "use a valid map");
}
