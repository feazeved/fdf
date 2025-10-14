/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xiaolin_utils2_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feazeved <feazeved@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 16:46:53 by feazeved          #+#    #+#             */
/*   Updated: 2025/10/10 16:31:05 by feazeved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

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
		ft_mlx_pixel_put(data, v->ypxl1, v->xpxl1,
			ft_apply_brightness(a.color, ft_rfpart(yend) * xgap));
		ft_mlx_pixel_put(data, v->ypxl1 + 1, v->xpxl1,
			ft_apply_brightness(a.color, ft_fpart(yend) * xgap));
	}
	else
	{
		ft_mlx_pixel_put(data, v->xpxl1, v->ypxl1,
			ft_apply_brightness(a.color, ft_rfpart(yend) * xgap));
		ft_mlx_pixel_put(data, v->xpxl1, v->ypxl1 + 1,
			ft_apply_brightness(a.color, ft_fpart(yend) * xgap));
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
		ft_mlx_pixel_put(data, v->ypxl2, v->xpxl2,
			ft_apply_brightness(b.color, ft_rfpart(yend) * xgap));
		ft_mlx_pixel_put(data, v->ypxl2 + 1, v->xpxl2,
			ft_apply_brightness(b.color, ft_fpart(yend) * xgap));
	}
	else
	{
		ft_mlx_pixel_put(data, v->xpxl2, v->ypxl2,
			ft_apply_brightness(b.color, ft_rfpart(yend) * xgap));
		ft_mlx_pixel_put(data, v->xpxl2, v->ypxl2 + 1,
			ft_apply_brightness(b.color, ft_fpart(yend) * xgap));
	}
}
