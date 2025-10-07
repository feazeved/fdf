/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transforms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feazeved <feazeved@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 20:57:38 by feazeved          #+#    #+#             */
/*   Updated: 2025/10/07 17:10:55 by feazeved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_rotate_x(int *y, int *z, double angle)
{
	int	prev_y;
	int	prev_z;

	prev_y = *y;
	prev_z = *z;
	*y = prev_y * cos(angle) - prev_z * sin(angle);
	*z = prev_y * sin(angle) + prev_z * cos(angle);
}

void	ft_rotate_y(int *x, int *z, double angle)
{
	int	prev_x;
	int	prev_z;

	prev_x = *x;
	prev_z = *z;
	*x = prev_x * cos(angle) + prev_z * sin(angle);
	*z = -prev_x * sin(angle) + prev_z * cos(angle);
}

void	ft_rotate_z(int *x, int *y, double angle)
{
	int	prev_x;
	int	prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = prev_x * cos(angle) - prev_y * sin(angle);
	*y = prev_x * sin(angle) + prev_y * cos(angle);
}

void	ft_project(t_point *point, t_camera *cam)
{
	int	x;
	int	y;
	int	z;

	x = point->x * cam->zoom;
	y = point->y * cam->zoom;
	z = point->z * cam->z_scale * cam->zoom;
	ft_rotate_x(&y, &z, cam->angle_x);
	ft_rotate_y(&x, &z, cam->angle_y);
	ft_rotate_z(&x, &y, cam->angle_z);
	point->screen_x = x + cam->offset_x;
	point->screen_y = y + cam->offset_y;
}
