/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xiaolin_algorithm.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feazeved <feazeved@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:03:33 by feazeved          #+#    #+#             */
/*   Updated: 2025/10/07 19:38:17 by feazeved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float   ft_fpart(float x)
{
    return (x - (int)x);
}

float ft_rfpart(float x)
{
    return (1.0f - ft_fpart(x));
}

void    ft_swap_coords(int *a, int *b)
{
    int temp;

    temp = *a;
    *a = *b;
    *b = temp;
}

void    ft_swap_points(t_point *a, t_point *b)
{
    int temp;

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

int ft_apply_brightness(int color, float brightness)
{
    int r;
    int g;
    int b;

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

void    ft_draw_aa_pixel(t_data *data, int x, int y, int color, float bright)
{
    int	final_color;

	final_color = ft_apply_brightness(color, bright);
	ft_mlx_pixel_put(data, x, y, final_color);
}

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

void	ft_wu_first_endpoint(t_data *data, t_point a, t_wu_vars *v, int steep)
{
	float	xend;
	float	yend;
	float	xgap;

	xend = (int)(a.screen_x + 0.5f);
	yend = a.screen_y + v->gradient * (xend - a.screen_x);
	xgap = ft_rfpart(a.screen_x + 0.5f);
	v->xpxl1 = xend;
	v->ypxl1 = (int)yend;
	if (steep)
	{
		ft_draw_aa_pixel(data, v->ypxl1, v->xpxl1, a.color,
			ft_rfpart(yend) * xgap);
		ft_draw_aa_pixel(data, v->ypxl1 + 1, v->xpxl1, a.color,
			ft_fpart(yend) * xgap);
	}
	else
	{
		ft_draw_aa_pixel(data, v->xpxl1, v->ypxl1, a.color,
			ft_rfpart(yend) * xgap);
		ft_draw_aa_pixel(data, v->xpxl1, v->ypxl1 + 1, a.color,
			ft_fpart(yend) * xgap);
	}
	v->intery = yend + v->gradient;
}

void	ft_wu_second_endpoint(t_data *data, t_point b, t_wu_vars *v, int steep)
{
	float	xend;
	float	yend;
	float	xgap;

	xend = (int)(b.screen_x + 0.5f);
	yend = b.screen_y + v->gradient * (xend - b.screen_x);
	xgap = ft_fpart(b.screen_x + 0.5f);
	v->xpxl2 = xend;
	v->ypxl2 = (int)yend;
	if (steep)
	{
		ft_draw_aa_pixel(data, v->ypxl2, v->xpxl2, b.color,
			ft_rfpart(yend) * xgap);
		ft_draw_aa_pixel(data, v->ypxl2 + 1, v->xpxl2, b.color,
			ft_fpart(yend) * xgap);
	}
	else
	{
		ft_draw_aa_pixel(data, v->xpxl2, v->ypxl2, b.color,
			ft_rfpart(yend) * xgap);
		ft_draw_aa_pixel(data, v->xpxl2, v->ypxl2 + 1, b.color,
			ft_fpart(yend) * xgap);
	}
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
		ft_draw_aa_pixel(data, (int)v->intery, x, color, ft_rfpart(v->intery));
		ft_draw_aa_pixel(data, (int)v->intery + 1, x, color,
			ft_fpart(v->intery));
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
		ft_draw_aa_pixel(data, x, (int)v->intery, color, ft_rfpart(v->intery));
		ft_draw_aa_pixel(data, x, (int)v->intery + 1, color,
			ft_fpart(v->intery));
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
