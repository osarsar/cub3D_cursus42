/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 00:43:01 by osarsar           #+#    #+#             */
/*   Updated: 2023/09/03 00:52:39 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	image(t_ply *data, int *i, int *j)
{
	if (data->map[*i][*j] == 'P')
	{
		mlx_put_image_to_window(data->mlx, data->win,
			data->back, *j * 50, *i * 50);
		mlx_put_image_to_window(data->mlx, data->win,
			data->player, *j * 50, *i * 50);
	}
	if (data->map[*i][*j] == 'E')
	{
		mlx_put_image_to_window(data->mlx, data->win,
			data->back, *j * 50, *i * 50);
		mlx_put_image_to_window(data->mlx, data->win,
			data->exit, *j * 50, *i * 50);
	}
	if (data->map[*i][*j] == 'C')
	{
		mlx_put_image_to_window(data->mlx, data->win,
			data->back, *j * 50, *i * 50);
		mlx_put_image_to_window(data->mlx, data->win,
			data->collect, *j * 50, *i * 50);
	}
}

void	image_window(t_ply *data, int *i, int *j)
{
	if (data->map[*i][*j] == '1')
		mlx_put_image_to_window(data->mlx, data->win,
			data->wall, *j * 50, *i * 50);
	image(data, i, j);
	if (data->map[*i][*j] == '0')
		mlx_put_image_to_window(data->mlx, data->win,
			data->back, *j * 50, *i * 50);
}

int	put_image_to_letter(t_ply *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			image_window(data, &i, &j);
			j++;
		}
		i++;
	}
	return (0);
}

void	put_image(t_ply *data)
{
	data->wall = mlx_xpm_file_to_image(data->mlx, "image/wall.xpm",
			&data->x, &data->y);
	data->player = mlx_xpm_file_to_image(data->mlx, "image/player.xpm",
			&data->x, &data->y);
	data->exit = mlx_xpm_file_to_image(data->mlx, "image/exit.xpm",
			&data->x, &data->y);
	data->collect = mlx_xpm_file_to_image(data->mlx, "image/collect.xpm",
			&data->x, &data->y);
	data->back = mlx_xpm_file_to_image(data->mlx, "image/back.xpm",
			&data->x, &data->y);
}
