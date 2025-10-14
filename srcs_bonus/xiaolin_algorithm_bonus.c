/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xiaolin_algorithm_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feazeved <feazeved@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:03:33 by feazeved          #+#    #+#             */
/*   Updated: 2025/10/10 16:30:45 by feazeved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	ft_wu_calc_gradient(t_point a, t_point b, float *gradient)
{
	float	dx;
	float	dy;

	dx = b.screen_x - a.screen_x;
	dy = b.screen_y - a.screen_y;
	if (dx == 0)
		*gradient = 1.0f;
	else
		*gradient = dy / dx;
}

int	ft_wu_prepare(t_point *a, t_point *b)
{
	int	steep;

	a->screen_x += 960;
	a->screen_y += 540;
	b->screen_x += 960;
	b->screen_y += 540;
	steep = abs(b->screen_y - a->screen_y) > abs(b->screen_x - a->screen_x);
	if (steep)
	{
		ft_swap_coords(&a->screen_x, &a->screen_y);
		ft_swap_coords(&b->screen_x, &b->screen_y);
	}
	if (a->screen_x > b->screen_x)
		ft_swap_points(a, b);
	return (steep);
}

void	ft_wu_draw_steep(t_data *data, t_point a, t_point b, t_wu_vars *v)
{
	int		x;
	int		color;
	float	ratio;

	x = v->xpxl1 + 1;
	while (x < v->xpxl2)
	{
		ratio = (float)(x - v->xpxl1) / (v->xpxl2 - v->xpxl1);
		color = ft_interpolate_color(a.color, b.color, ratio);
		ft_mlx_pixel_put(data, (int)v->intery, x,
			ft_apply_brightness(color, ft_rfpart(v->intery)));
		ft_mlx_pixel_put(data, (int)v->intery + 1, x,
			ft_apply_brightness(color, ft_fpart(v->intery)));
		v->intery += v->gradient;
		x++;
	}
}

void	ft_wu_draw_gentle(t_data *data, t_point a, t_point b, t_wu_vars *v)
{
	int		x;
	int		color;
	float	ratio;

	x = v->xpxl1 + 1;
	while (x < v->xpxl2)
	{
		ratio = (float)(x - v->xpxl1) / (v->xpxl2 - v->xpxl1);
		color = ft_interpolate_color(a.color, b.color, ratio);
		ft_mlx_pixel_put(data, x, (int)v->intery,
			ft_apply_brightness(color, ft_rfpart(v->intery)));
		ft_mlx_pixel_put(data, x, (int)v->intery + 1,
			ft_apply_brightness(color, ft_fpart(v->intery)));
		v->intery += v->gradient;
		x++;
	}
}

void	ft_draw_wu_line(t_data *data, t_point a, t_point b)
{
	t_wu_vars	v;
	int			steep;

	steep = ft_wu_prepare(&a, &b);
	ft_wu_calc_gradient(a, b, &v.gradient);
	ft_wu_first_endpoint(data, a, &v, steep);
	ft_wu_second_endpoint(data, b, &v, steep);
	if (steep)
		ft_wu_draw_steep(data, a, b, &v);
	else
		ft_wu_draw_gentle(data, a, b, &v);
}
