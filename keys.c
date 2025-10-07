/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feazeved <feazeved@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 20:24:18 by feazeved          #+#    #+#             */
/*   Updated: 2025/10/07 17:14:18 by feazeved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_handle_movement(int keycode, t_data *data)
{
	if (keycode == 65362)
		data->camera.offset_y -= 10;
	else if (keycode == 65364)
		data->camera.offset_y += 10;
	else if (keycode == 65361)
		data->camera.offset_x -= 10;
	else if (keycode == 65363)
		data->camera.offset_x += 10;
	else if (keycode == 65365)
	{
		if (data->camera.z_scale < 10)
			data->camera.z_scale *= 1.1;
	}
	else if (keycode == 65366)
	{
		if (data->camera.z_scale > 0.1)
			data->camera.z_scale *= 0.9;
	}
	else
		return (0);
	return (1);
}

int	ft_handle_rotation(int keycode, t_data *data)
{
	if (keycode == 113)
		data->camera.angle_x -= 0.1;
	else if (keycode == 119)
		data->camera.angle_x += 0.1;
	else if (keycode == 97)
		data->camera.angle_y -= 0.1;
	else if (keycode == 115)
		data->camera.angle_y += 0.1;
	else if (keycode == 122)
		data->camera.angle_z -= 0.1;
	else if (keycode == 120)
		data->camera.angle_z += 0.1;
	else
		return (0);
	return (1);
}

int	ft_handle_zoom(int keycode, t_data *data)
{
	if (keycode == 61 || keycode == 65451)
	{
		if (data->camera.zoom < 100)
			data->camera.zoom += 2;
		return (1);
	}
	if (keycode == 45 || keycode == 65453)
	{
		if (data->camera.zoom > 0)
		{
			if (data->camera.zoom > 2)
				data->camera.zoom -= 2;
			else
				data->camera.zoom = 1;
		}
		return (1);
	}
	if (keycode == 4)
	{
		data->camera.zoom += 1;
		return (1);
	}
	if (keycode == 5)
	{
		if (data->camera.zoom > 1)
			data->camera.zoom -= 1;
		return (1);
	}
	return (0);
}

int	key_hook(int keycode, t_data *data)
{
	printf("Keycode pressed: %d\n", keycode);
	if (keycode == 65307)
	{
		ft_free_data(data);
		exit(0);
	}
	if (keycode == 114)
		ft_reset_camera(data);
	else if (keycode == 108)
		data->wu_line = !data->wu_line;
	else if (ft_handle_zoom(keycode, data))
		return (0);
	else if (ft_handle_rotation(keycode, data))
		return (0);
	else if (ft_handle_movement(keycode, data))
		return (0);
	else
		return (0);
	return (0);
}

int	mouse_hook(int keycode, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (keycode == 4)
	{
		if (data->camera.zoom < 100)
			data->camera.zoom += 1;
	}
	else if (keycode == 5)
	{
		data->camera.zoom -= 5;
		if (data->camera.zoom < 1)
			data->camera.zoom = 1;
	}
	return (0);
}
