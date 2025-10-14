/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feazeved <feazeved@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 20:24:18 by feazeved          #+#    #+#             */
/*   Updated: 2025/10/09 15:34:51 by feazeved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

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
	if (keycode == 46)
		data->keys.add_rot_speed = true;
	if (keycode == 44)
		data->keys.sub_rot_speed = true;
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
	if (keycode == 46)
		data->keys.add_rot_speed = false;
	if (keycode == 44)
		data->keys.sub_rot_speed = false;
	return (0);
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
