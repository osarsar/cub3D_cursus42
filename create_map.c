/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 08:11:49 by osarsar           #+#    #+#             */
/*   Updated: 2023/09/21 00:09:20 by osarsar          ###   ########.fr       */
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
	if (data->map[data->x][data->y] == '1'
		|| data->map[data->x][data->y] == '=')
		my_mlx_pixel_put(data->mydata, i, j, 0x808080);
	else if (data->map[data->x][data->y] == '0')
		my_mlx_pixel_put(data->mydata, i, j, 0x00FFFFFF);
	else if (data->map[data->x][data->y] == 'N'
		|| data->map[data->x][data->y] == 'S'
		|| data->map[data->x][data->y] == 'W'
		|| data->map[data->x][data->y] == 'E')
	{
		my_mlx_pixel_put(data->mydata, i, j, 0x00FFFFFF);
		if (data->p_x == 0 && data->p_y == 0)
		{
			data->p_x = i + (NUM_PIXELS / 2);
			data->p_y = j + (NUM_PIXELS / 2);
			view_to_start(data);
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
		data->nb_x += NUM_PIXELS;
	}
}

int	creat_map(t_ply *data)
{
	data->x = 0;
	data->nb_y = NUM_PIXELS;
	data->start_j = 0;
	while (data->map[data->x])
	{
		data->y = 0;
		data->nb_x = NUM_PIXELS;
		creat_map_line(data);
		data->nb_y += NUM_PIXELS;
		data->start_j += NUM_PIXELS;
		data->x++;
	}
	put_player(data);
	fov_player(data);
	mlx_put_image_to_window(data->mlx, data->win, data->mydata->img, 0, 0);
	return (0);
}
