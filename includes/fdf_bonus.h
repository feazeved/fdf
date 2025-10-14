/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feazeved <feazeved@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 23:21:57 by feazeved          #+#    #+#             */
/*   Updated: 2025/10/14 16:27:41 by feazeved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
# define FDF_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include "libft.h"
# include "mlx.h"
# include "structs_bonus.h"
# include <X11/keysym.h>

# define GRAY 2829099

// FDF ----------------------------------------------------------------------
// --------------------------------------------------------------------------
// main e error
void	ft_error(t_data *data, char *func, char *msg);
void	ft_free_data(t_data *data);
void	ft_help_menu(t_data *data);

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
void	ft_check_map(t_data *data, char **argv);

// minilibx
void	ft_mlx_pixel_put(t_data *data, int x, int y, int color);
int		ft_close_window(t_data *data);
int		ft_render(t_data *data);
void	ft_clear_image(t_data *data);
void	ft_init_window(t_data *data);
void	ft_display_info(t_data *data);
void	ft_display_menu(t_data *data, int first_y, int last_y, int last_x);

// camera and controls
void	ft_init_camera(t_data *data);
void	ft_reset_camera(t_data *data);
int		key_hook(int keycode, t_data *data);
int		ft_handle_movement(t_data *data);
int		ft_handle_rotation(t_data *data);
int		ft_handle_zoom(t_data *data);
int		mouse_hook(int keycode, int x, int y, t_data *data);
int		handle_zoom(t_data *data, int keycode, float increase);
void	handle_smooth_zoom(int *limit_in, int *limit_out, float increase);
void	ft_set_zoom(t_data *data, int max_dimension);
void	update(t_data *data);
int		key_release(int keycode, t_data *data);
int		key_press(int keycode, t_data *data);
void	set_rotations(int keycode, t_data *data, bool set);

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
void	ft_draw_map(t_data *data, int y, int skip);
void	ft_draw_line_toggle(t_data *data, int p1, int p2);

// xiaolin
void	ft_draw_wu_line(t_data *data, t_point a, t_point b);
float	ft_fpart(float x);
float	ft_rfpart(float x);
void	ft_swap_points(t_point *a, t_point *b);
void	ft_swap_coords(int *a, int *b);
int		ft_apply_brightness(int color, float brightness);
void	ft_wu_first_endpoint(t_data *data, t_point a, t_wu_vars *v, int steep);
void	ft_wu_second_endpoint(t_data *data, t_point b, t_wu_vars *v, int steep);

#endif
