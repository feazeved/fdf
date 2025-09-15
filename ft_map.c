/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feazeved <feazeved@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 19:08:14 by feazeved          #+#    #+#             */
/*   Updated: 2025/09/15 23:21:23 by feazeved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
}	t_point;

typedef struct s_map
{
	int	width;
	int	height;
	int	np;
	t_point *points;
}	t_map;

typedef struct s_data
{
	t_map map;
}	t_data;

t_data	*ft_parsing(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2)
	{
		perror();
	}
	data = (t_data *)ft_fdf_calloc(1, sizeof(t_data));
	ft_set_map_size(data, argv);
	ft_set_numbers(0, data, argv);
	return (data);
}

int	ft_atoi(char *str)
{
	int	sign;
	int	num;
	int	i;

	i = 0;
	sign = 1;
	num = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		num = (str[i] - '0') + (num * 10);
		i++;
	}
	return (num * sign)
}

void	ft_set_point(t_point *point, int y, int x, int z)
{
	point->x = x;
	point->y = y;
	point->z = z;
}

void	ft_set_numbers(int i, t_data *data, char **argv)
{
	int		j
	int		fd;
	char	*line;
	char	**split;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_error(data);
	data->map.np = (data->map.width) * (data->map.height);
	data->map.points = (t_point *)ft_fdf_calloc(data->map.np, sizeof(t_point));
	while (i < data->map.height)
	{
		j = 0;
		line = ft_gnl(fd, data);
		split = ft_my_split(line, ' ', data);
		while (j < data->map.width)
		{
			ft_set_point(&(data->map->points[i]), i, j, ft_atoi(split[j]));
			j++;
		}
		i++;
	}
}

char	*ft_gnl(int fd, t_data *data)
{



}


char	**ft_my_split(char *str, char sep, t_data *data)
{
	char	**split
	int		i;
	int		j;

	i = 0;
	j = 0;
	split = (char **)ft_fdf_calloc(ft_count_words(str, sep) + 1, sizeof(char *));
	while (str[i])
	{
		

	}
	return (split);
}

void	*ft_fdf_calloc(int nmemb, size_t size)
{
	unsigned char	*str;
	size_t			i;
	size_t			sum;

	i = 0;
	sum = nmemb * size;
	data = malloc(sum);
	if (!data)
		ft_error(data);
	while (i < sum)
	{
		str[i] = 0;
		i++;
	}
	return (str);
}

int	ft_count_words(char *str, char sep)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (str && str[i])
	{
		while (str[i] == sep)
			i++;
		if (str[i])
			words++;
		while (str[i] && str[i] != sep)
			i++;
	}
	return (words);
}

void	ft_set_map_size(t_data *data, char **argv)
{
	int		height;
	int		fd;
	char	*line;
	int		width;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_error(data);
	height = 0;
	width = 0;
	while (1)
	{
		line = ft_gnl(fd, data);
		if (!line)
			break ;
		if (!width)
			width = ft_count_words(line, ' ');
		free(line);
		height++;
	}
	data->map.height = height;
	data->map.width = width;
	close(fd);
}

char *onde_esta_o_afonso(time_t now)
{
	(void) now;
	return ("a fumar");
}

