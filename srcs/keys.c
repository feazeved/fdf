/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feazeved <feazeved@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 20:24:18 by feazeved          #+#    #+#             */
/*   Updated: 2025/10/09 15:34:51 by feazeved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_handle_movement(t_data *data)
{
	if (data->keys.up_arrow)
		data->camera.offset_y -= 1;
	if (data->keys.down_arrow)
		data->camera.offset_y += 1;
	if (data->keys.left_arrow)
		data->camera.offset_x -= 1;
	if (data->keys.right_arrow)
		data->camera.offset_x += 1;
	if (data->keys.page_up)
	{
		data->camera.z_scale *= 1.1;
		if (data->camera.z_scale > 0.5)
			data->camera.z_scale = 0.5;
	}
	if (data->keys.page_down)
	{
		data->camera.z_scale *= 0.9;
		if (data->camera.z_scale < 0.1)
			data->camera.z_scale = 0.1;
	}
	return (0);
}

int	ft_handle_rotation(t_data *data)
{
	if (data->keys.s)
		data->camera.angle_x -= 0.1;
	if (data->keys.w)
		data->camera.angle_x += 0.1;
	if (data->keys.a)
		data->camera.angle_y -= 0.1;
	if (data->keys.d)
		data->camera.angle_y += 0.1;
	if (data->keys.q)
		data->camera.angle_z -= 0.1;
	if (data->keys.e)
		data->camera.angle_z += 0.1;
	return (0);
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

void	set_rotations(int keycode, t_data *data, bool set)
{
	if (keycode == XK_w)
		data->keys.w = set;
	if (keycode == XK_a)
		data->keys.a = set;
	if (keycode == XK_s)
		data->keys.s = set;
	if (keycode == XK_d)
		data->keys.d = set;
	if (keycode == XK_q)
		data->keys.q = set;
	if (keycode == XK_e)
		data->keys.e = set;
}

int	key_press(int keycode, t_data *data)
{
	key_hook(keycode, data);
	set_rotations(keycode, data, true);
	if (keycode == XK_Right)
		data->keys.right_arrow = true;
	if (keycode == XK_Left)
		data->keys.left_arrow = true;
	if (keycode == XK_Up)
		data->keys.up_arrow = true;
	if (keycode == XK_Down)
		data->keys.down_arrow = true;
	if (keycode == 61)
		data->keys.plus = true;
	if (keycode == XK_minus)
		data->keys.minus = true;
	if (keycode == XK_Page_Up)
		data->keys.page_up = true;
	if (keycode == XK_Page_Down)
		data->keys.page_down = true;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	set_rotations(keycode, data, false);
	if (keycode == XK_Right)
		data->keys.right_arrow = false;
	if (keycode == XK_Left)
		data->keys.left_arrow = false;
	if (keycode == XK_Up)
		data->keys.up_arrow = false;
	if (keycode == XK_Down)
		data->keys.down_arrow = false;
	if (keycode == 61)
		data->keys.plus = false;
	if (keycode == XK_minus)
		data->keys.minus = false;
	if (keycode == XK_Page_Up)
		data->keys.page_up = false;
	if (keycode == XK_Page_Down)
		data->keys.page_down = false;
	return (0);
}

void	update(t_data *data)
{
	ft_handle_zoom(data);
	ft_handle_rotation(data);
	ft_handle_movement(data);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == 65307)
	{
		ft_free_data(data);
		exit(0);
	}
	if (keycode == XK_h)
		data->help_menu = !data->help_menu;
	if (keycode == XK_r)
		ft_reset_camera(data);
	if (keycode == XK_p)
		data->camera.parallel = !data->camera.parallel;
	if (keycode == XK_l)
		data->wu_line = !data->wu_line;
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
