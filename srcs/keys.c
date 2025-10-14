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

int	key_press(int keycode, t_data *data)
{
	key_hook(keycode, data);
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
	return (0);
}

int	key_release(int keycode, t_data *data)
{
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
	return (0);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == 65307)
	{
		ft_free_data(data);
		exit(0);
	}
	return (0);
}
