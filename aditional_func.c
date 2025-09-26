/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aditional_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feazeved <feazeved@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 19:36:48 by feazeved          #+#    #+#             */
/*   Updated: 2025/09/24 20:29:47 by feazeved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
