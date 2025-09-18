/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feazeved <feazeved@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 19:34:58 by feazeved          #+#    #+#             */
/*   Updated: 2025/09/16 23:26:28 by feazeved         ###   ########.fr       */
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

// STRUCTS -------------------------------------------------------------------
// ---------------------------------------------------------------------------
typedef struct s_point
{
	int	x;
	int	y;
	int	z;
}		t_point;

typedef struct s_map
{
	int		width;
	int		height;
	int		np;
	t_point	*points;
}			t_map;

typedef struct s_data
{
	t_map	map;
  int   w_width;
  int   w_height;
  void  *mlx;
  void  *mlx_win;
  void  *img;
  char  *addr;
  int   bpp;
  int   line_len;
  int   endian;
	char	*line;
	char	**split;
}			t_data;

// FDF ----------------------------------------------------------------------
// --------------------------------------------------------------------------
void	ft_error(t_data *data, char *func, char *msg);
void	ft_free_data(t_data *data);
void	ft_parsing(t_data *data, int argc, char **argv);
void	ft_set_point(t_point *point, int y, int x, char *str);
void	ft_set_numbers(int i, t_data *data, char **argv);
void	*ft_fdf_calloc(int nmemb, size_t size, t_data *data);
int		ft_count_words(char *str, char sep);
void	ft_set_map_size(t_data *data, char **argv);

// LIBFT --------------------------------------------------------------------
// --------------------------------------------------------------------------
char	**ft_split(const char *s, char c);
void	*ft_calloc(size_t nmemb, size_t size);
size_t	ft_strlen(const char *str);
char	*get_next_line(int fd);
void	ft_free_strs(char **strs);

#endif
