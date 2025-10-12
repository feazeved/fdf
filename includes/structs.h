#ifndef STRUCTS_H
# define STRUCTS_h

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
	int		auto_rotate;
	float	rotate_speed;
	int		parallel;
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

#endif