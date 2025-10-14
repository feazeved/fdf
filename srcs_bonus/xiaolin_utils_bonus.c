/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xiaolin_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feazeved <feazeved@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 16:43:16 by feazeved          #+#    #+#             */
/*   Updated: 2025/10/09 16:43:44 by feazeved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

float	ft_fpart(float x)
{
	return (x - (int)x);
}

float	ft_rfpart(float x)
{
	return (1.0f - ft_fpart(x));
}

void	ft_swap_coords(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	ft_swap_points(t_point *a, t_point *b)
{
	int	temp;

	temp = a->screen_x;
	a->screen_x = b->screen_x;
	b->screen_x = temp;
	temp = a->screen_y;
	a->screen_y = b->screen_y;
	b->screen_y = temp;
	temp = a->color;
	a->color = b->color;
	b->color = temp;
}

int	ft_apply_brightness(int color, float brightness)
{
	int	r;
	int	g;
	int	b;

	r = ((color >> 16) & 0xFF) * brightness;
	g = ((color >> 8) & 0xFF) * brightness;
	b = (color & 0xFF) * brightness;
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	return ((r << 16) | (g << 8) | b);
}
