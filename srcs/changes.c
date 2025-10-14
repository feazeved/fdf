/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   changes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feazeved <feazeved@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 22:08:22 by feazeved          #+#    #+#             */
/*   Updated: 2025/10/13 22:09:24 by feazeved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	update(t_data *data)
{
	ft_handle_zoom(data);
	ft_handle_movement(data);
}

int	ft_handle_movement(t_data *data)
{
	if (data->keys.up_arrow)
		data->camera.offset_y -= 2;
	if (data->keys.down_arrow)
		data->camera.offset_y += 2;
	if (data->keys.left_arrow)
		data->camera.offset_x -= 2;
	if (data->keys.right_arrow)
		data->camera.offset_x += 2;
	return (0);
}

int	mouse_hook(int keycode, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (keycode == 4)
	{
		data->camera.zoom += data->camera.zoom_increase;
		if (data->camera.zoom > data->camera.zoom_limit_out)
			data->camera.zoom = data->camera.zoom_limit_out;
	}
	else if (keycode == 5)
	{
		data->camera.zoom -= data->camera.zoom_increase;
		if (data->camera.zoom < data->camera.zoom_limit_in)
			data->camera.zoom = data->camera.zoom_limit_in;
	}
	return (1);
}

int	ft_handle_zoom(t_data *data)
{
	if (data->keys.plus)
	{
		data->camera.zoom += data->camera.zoom_increase;
		if (data->camera.zoom > data->camera.zoom_limit_out)
			data->camera.zoom = data->camera.zoom_limit_out;
	}
	else if (data->keys.minus)
	{
		data->camera.zoom -= data->camera.zoom_increase;
		if (data->camera.zoom < data->camera.zoom_limit_in)
			data->camera.zoom = data->camera.zoom_limit_in;
	}
	return (0);
}
