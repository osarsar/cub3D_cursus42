/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 08:11:49 by osarsar           #+#    #+#             */
/*   Updated: 2023/09/10 08:16:54 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	put_pixel_to_image(t_ply *data, int i, int j)
{
	if (data->map[data->x][data->y] == '1')
		my_mlx_pixel_put(data->data, i, j, 0x808080);
	else if (data->map[data->x][data->y] == '0')
		my_mlx_pixel_put(data->data, i, j, 0x00FFFFFF);
	else if (data->map[data->x][data->y] == 'N')
	{
		my_mlx_pixel_put(data->data, i, j, 0x00FFFFFF);
		if (data->o_x == 0 && data->o_y == 0)
		{
			data->o_x = i + (80 / 2);
			data->o_y = j + (80 / 2);
		}
	}
}

void	creat_map_line(t_ply *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	data->y = 0;
	while (data->map[data->x][data->y])
	{
		while (i < data->nb_x)
		{
			j = data->start_j;
			while (j < data->nb_y)
			{
				put_pixel_to_image(data, i, j);
				j++;
			}
			i++;
		}
		data->y++;
		data->nb_x += 80;
	}
}

int	creat_map(t_ply *data)
{
	data->x = 0;
	data->nb_y = 80;
	data->start_j = 0;
	while (data->map[data->x])
	{
		data->y = 0;
		data->nb_x = 80;
		creat_map_line(data);
		data->nb_y += 80;
		data->start_j += 80;
		data->x++;
	}
	put_player(data);
	fov_player(data);
	mlx_put_image_to_window(data->mlx, data->win, data->data->img, 0, 0);
	return (0);
}
