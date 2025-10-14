/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feazeved <feazeved@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 16:18:55 by feazeved          #+#    #+#             */
/*   Updated: 2025/10/09 18:52:12 by feazeved         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_check_map(t_data *data, char **argv)
{
	int	i;

	i = 0;
	while (argv[1][i])
		i++;
	if (i > 4)
	{
		i -= 4;
		if (argv[1][i] != '.' || argv[1][i + 1] != 'f' || argv[1][i + 2] != 'd'
			|| argv[1][i + 3] != 'f')
			ft_error(data, "File", "use a valid map");
	}
	else
		ft_error(data, "File", "use a valid map");
}
