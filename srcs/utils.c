/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feazeved <feazeved@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 20:54:35 by feazeved          #+#    #+#             */
/*   Updated: 2025/10/06 22:18:26 by feazeved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_ahextoint(char *str)
{
	int	result;
	int	digit;

	result = 0;
	while (*str && ft_ishexdigit(*str))
	{
		digit = 0;
		if (*str >= '0' && *str <= '9')
			digit = *str - '0';
		else if (*str >= 'a' && *str <= 'f')
			digit = *str - 'a' + 10;
		else if (*str >= 'A' && *str <= 'F')
			digit = *str - 'A' + 10;
		result = result * 16 + digit;
		str++;
	}
	return (result);
}

int	ft_ishexdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else if ((c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'))
		return (1);
	else
		return (0);
}

void	ft_center_points(t_data *data)
{
	int	middle_x;
	int	middle_y;
	int	i;

	middle_y = data->map.height / 2;
	middle_x = data->map.width / 2;
	data->map.center = &data->map.points[middle_y * data->map.width + middle_x];
	i = 0;
	while (i < data->map.np)
	{
		data->map.points[i].x -= middle_x;
		data->map.points[i].y -= middle_y;
		i++;
	}
}

void	ft_set_z_limits(t_data *data)
{
	int	min;
	int	max;
	int	i;

	if (!data)
		return ;
	min = INT_MAX;
	max = INT_MIN;
	i = 0;
	while (i < data->map.np)
	{
		if (data->map.points[i].z < min)
			min = data->map.points[i].z;
		if (data->map.points[i].z > max)
			max = data->map.points[i].z;
		i++;
	}
	data->map.z_min = min;
	data->map.z_max = max;
}

void	ft_init_line(t_point *a, t_point *b, int *delta, float *slope)
{
	delta[0] = abs(b->screen_x - a->screen_x);
	delta[1] = abs(b->screen_y - a->screen_y);
	if (delta[0] > delta[1])
	{
		if (delta[0] != 0)
			*slope = (float)delta[1] / delta[0];
		else
			*slope = 0;
	}
	else
	{
		if (delta[1] != 0)
			*slope = (float)delta[0] / delta[1];
		else
			*slope = 0;
	}
}
