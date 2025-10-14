/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feazeved <feazeved@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 16:27:20 by feazeved          #+#    #+#             */
/*   Updated: 2025/10/11 17:33:15 by suassuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_init_camera(t_data *data)
{
	int	max_dimension;

	max_dimension = data->map.width;
	if (data->map.height > max_dimension)
		max_dimension = data->map.height;
	data->camera.scale = 1.0;
	data->camera.angle_x = 0.5;
	data->camera.angle_y = -0.5;
	data->camera.angle_z = 0.523599;
	data->camera.offset_x = 0;
	data->camera.offset_y = 0;
	data->camera.z_scale = 0.25;
	ft_set_zoom(data, max_dimension);
	if (max_dimension <= 50)
		data->camera.zoom = 50;
	else if (max_dimension <= 100)
		data->camera.zoom = 15;
	else if (max_dimension <= 200)
		data->camera.zoom = 4;
	else
		data->camera.zoom = 2;
}

void	ft_set_zoom(t_data *data, int max_dimension)
{
	if (max_dimension <= 99)
	{
		data->camera.zoom_increase = 2;
		data->camera.zoom_limit_in = 10;
		data->camera.zoom_limit_out = 100;
	}
	else if (max_dimension >= 100 && max_dimension < 200)
	{
		data->camera.zoom_increase = 0.6;
		data->camera.zoom_limit_in = 8;
		data->camera.zoom_limit_out = 25;
	}
	else
	{
		data->camera.zoom_increase = 0.2;
		data->camera.zoom_limit_in = 1;
		data->camera.zoom_limit_out = 10;
	}
}
