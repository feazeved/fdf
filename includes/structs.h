/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feazeved <feazeved@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:52:30 by feazeved          #+#    #+#             */
/*   Updated: 2025/10/13 15:00:22 by feazeved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	int		screen_x;
	int		screen_y;
	int		color;
}		t_point;

typedef struct s_map
{
	int		width;
	int		height;
	int		np;
	t_point	*points;
	t_point	*center;
	int		z_min;
	int		z_max;
}			t_map;

typedef struct s_camera
{
	double	scale;
	double	angle_x;
	double	angle_y;
	double	angle_z;
	double	zoom;
	int		offset_x;
	int		offset_y;
	double	z_scale;
	float	zoom_limit_in;
	float	zoom_limit_out;
	float	zoom_increase;
}			t_camera;

typedef struct s_keys
{
	bool	plus;
	bool	minus;
	bool	up_arrow;
	bool	down_arrow;
	bool	left_arrow;
	bool	right_arrow;
}	t_keys;

typedef struct s_data
{
	t_map		map;
	int			fd;
	int			w_width;
	int			w_height;
	void		*mlx;
	void		*mlx_win;
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	t_camera	camera;
	char		*line;
	char		**split;
	t_keys		keys;
}				t_data;

#endif
