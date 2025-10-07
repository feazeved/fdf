/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feazeved <feazeved@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 19:34:58 by feazeved          #+#    #+#             */
/*   Updated: 2025/10/07 17:40:37 by feazeved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define BUFFER_SIZE 256

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include "mlx.h"
# include <limits.h>
# include <math.h>

// STRUCTS -------------------------------------------------------------------
// ---------------------------------------------------------------------------
typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	screen_x;
	int	screen_y;
	int	color;
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
	int		zoom;
	int		offset_x;
	int		offset_y;
	double	z_scale;
}			t_camera;

typedef struct s_data
{
	t_map		map;
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
	int			wu_line;
}				t_data;

typedef struct s_wu_vars
{
	float	gradient;
	float	intery;
	int		xpxl1;
	int		ypxl1;
	int		xpxl2;
	int		ypxl2;
}	t_wu_vars;

// FDF ----------------------------------------------------------------------
// --------------------------------------------------------------------------
// main e error
void	ft_error(t_data *data, char *func, char *msg);
void	ft_free_data(t_data *data);



// parsing
void	ft_parsing(t_data *data, int argc, char **argv);
void	ft_set_point(t_point *point, int y, int x, char *str);
void	ft_set_numbers(int i, t_data *data, char **argv);
void	ft_set_point_color(t_point *point, int y, int x, char *str);
void	*ft_fdf_calloc(int nmemb, size_t size, t_data *data);
void	ft_set_map_size(t_data *data, char **argv);
void	ft_set_z_limits(t_data *data);
int		ft_parse_color(char **str);
int		ft_ishexdigit(char c);
int		ft_ahextoint(char *str);
void	ft_center_points(t_data *data);




// minilibx
void	ft_mlx_pixel_put(t_data *data, int x, int y, int color);
int		ft_close_window(t_data *data);
int		ft_render(t_data *data);
void	ft_clear_image(t_data *data);
void	ft_init_window(t_data *data);




// camera and controls
void	ft_init_camera(t_data *data);
void	ft_reset_camera(t_data *data);
int		key_hook(int keycode, t_data *data);
int		ft_handle_movement(int keycode, t_data *data);
int		ft_handle_rotation(int keycode, t_data *data);
int		ft_handle_zoom(int keycode, t_data *data);
int		mouse_hook(int keycode, int x, int y, t_data *data);

// projection and rotations
void	ft_project(t_point *point, t_camera *cam);
void	ft_rotate_z(int *x, int *y, double angle);
void	ft_rotate_y(int *x, int *z, double angle);
void	ft_rotate_x(int *y, int *z, double angle);

// colors
int		ft_get_color_from_height(t_data *data, int z);
void	ft_assign_colors(t_data *data);
int		ft_interpolate_color(int c1, int c2, double ratio);


// drawing
void	ft_init_line(t_point *a, t_point *b, int *delta, float *slope);
void	ft_draw_horizontal(t_data *data, t_point a, t_point b);
void	ft_draw_vertical(t_data *data, t_point a, t_point b);
void	ft_drawline(t_data *data, t_point a, t_point b);
void	ft_draw_map(t_data *data);

void	ft_draw_line_toggle(t_data *data, int p1, int p2);


// xiaolin
void	ft_draw_wu_line(t_data *data, t_point a, t_point b);
float	ft_fpart(float x);
float	ft_rfpart(float x);
void	ft_swap_points(t_point *a, t_point *b);
void	ft_swap_coords(int *a, int *b);
void	ft_draw_aa_pixel(t_data *data, int x, int y, int color, float bright);
int		ft_apply_brightness(int color, float brightness);

// LIBFT --------------------------------------------------------------------
// --------------------------------------------------------------------------
char	**ft_split(const char *s, char c);
void	*ft_calloc(size_t nmemb, size_t size);
size_t	ft_strlen(const char *str);
char	*get_next_line(int fd);
void	ft_free_strs(char **strs);
void	*ft_memset(void *s, int c, size_t n);
int		ft_count_words(char *str, char sep);

#endif
