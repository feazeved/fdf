/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feazeved <feazeved@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 15:20:52 by feazeved          #+#    #+#             */
/*   Updated: 2025/09/16 22:51:13 by feazeved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"

void	ft_test_parsing(t_map map)
{
	int	i;

	i = 0;
	while (i < map.np)
	{
		printf("point: %d ", i);
		printf("x == %d   ", map.points[i].x);
		printf("y == %d   ", map.points[i].y);
		printf("z == %d\n", map.points[i].z);
		i++;
	}
}

void  ft_init_window(t_data *data)
{
  data->w_width = 1920;
  data->w_height = 1080;
  data->mlx = mlx_init();
  if (!data->mlx)
    ft_error(data, "Mlx_init", "could not initialize mlx");
  data->mlx_win = mlx_new_window(data->mlx, data->w_width, data->w_height, "FDF feazeved");
  if (!data->mlx_win)
    ft_error(data, "Mlx_new_window", "could not create a new window");
  data->img = mlx_new_image(data->mlx, data->w_width, data->w_height);
  if (!data->img)
    ft_error(data, "Mlx_new_image", "could not create a new image");
  data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->line_len, &data->endian);
  if (!data->addr)
    ft_error(data, "Mlx_get_data_addr", "could not get data addr");
}

int	main(int argc, char **argv)
{
	t_data	data;

	ft_parsing(&data, argc, argv);
  ft_init_window(&data);
	ft_test_parsing(data.map);
	ft_free_data(&data);
	return (0);
}
