/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feazeved <feazeved@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 17:36:49 by feazeved          #+#    #+#             */
/*   Updated: 2025/10/14 18:00:10 by feazeved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_get_color_from_height(t_data *data, int z)
{
	double	ratio;
	int		r;
	int		g;
	int		b;

	if (data->map.z_max == data->map.z_min)
		return (0x00FF00);
	ratio = (double)(z - data->map.z_min) / (data->map.z_max - data->map.z_min);
	if (ratio < 0.5)
	{
		r = 0;
		g = (int)(255 * (ratio * 2));
		b = (int)(255 * (1 - ratio * 2));
	}
	else
	{
		r = (int)(255 * ((ratio - 0.5) * 2));
		g = (int)(255 * (1 - (ratio - 0.5) * 2));
		b = 0;
	}
	return ((r << 16) | (g << 8) | b);
}

void	ft_assign_colors(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->map.np)
	{
		if (data->map.points[i].color == -1)
			data->map.points[i].color
				= ft_get_color_from_height(data, data->map.points[i].z);
		i++;
	}
}

int	ft_interpolate_color(int c1, int c2, double ratio)
{
	int	r;
	int	g;
	int	b;

	r = ((c1 >> 16) & 0xFF) + (int)((((c2 >> 16) & 0xFF)
				- ((c1 >> 16) & 0xFF)) * ratio);
	g = ((c1 >> 8) & 0xFF) + (int)((((c2 >> 8) & 0xFF)
				- ((c1 >> 8) & 0xFF)) * ratio);
	b = (c1 & 0xFF) + (int)(((c2 & 0xFF)
				- (c1 & 0xFF)) * ratio);
	return ((r << 16) | (g << 8) | b);
}
