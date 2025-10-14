/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feazeved <feazeved@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 20:53:21 by feazeved          #+#    #+#             */
/*   Updated: 2025/10/11 17:33:32 by suassuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	ft_error(t_data *data, char *func, char *msg)
{
	if (func)
	{
		write(2, func, ft_strlen(func));
		write(2, ": ", 2);
	}
	if (msg)
		write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	if (data)
		ft_free_data(data);
	exit(69);
}

void	ft_free_data(t_data *data)
{
	if (data->fd != -1)
		close(data->fd);
	if (data && data->map.points)
		free(data->map.points);
	if (data && data->line)
		free(data->line);
	if (data && data->split)
		ft_free_strs(data->split);
	if (data && data->mlx)
	{
		mlx_destroy_image(data->mlx, data->img);
		mlx_destroy_window(data->mlx, data->mlx_win);
		mlx_destroy_display(data->mlx);
	}
	if (data && data->mlx)
		free(data->mlx);
	exit(0);
}

void	*ft_fdf_calloc(int nmemb, size_t size, t_data *data)
{
	unsigned char	*str;
	size_t			i;
	size_t			sum;

	i = 0;
	sum = nmemb * size;
	str = malloc(sum);
	if (!str)
		ft_error(data, "Malloc", strerror(errno));
	while (i < sum)
	{
		str[i] = 0;
		i++;
	}
	return (str);
}
