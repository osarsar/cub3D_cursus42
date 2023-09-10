/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 08:15:37 by osarsar           #+#    #+#             */
/*   Updated: 2023/09/10 08:35:22 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	put_player(t_ply *data)
{
	data->start_x = data->o_x - data->radius;
	data->end_x = data->o_x + data->radius;
	data->start_y = data->o_y - data->radius;
	data->end_y = data->o_y + data->radius;
	data->x = data->start_x;
	while (data->x <= data->end_x)
	{
		data->y = data->start_y;
		while (data->y <= data->end_y)
		{
			if (((data->x - data->o_x) * (data->x - data->o_x))
				+ ((data->y - data->o_y) * (data->y - data->o_y))
				<= (data->radius * data->radius))
				my_mlx_pixel_put(data->data, data->x, data->y, 0x00FF0000);
			data->y++;
		}
		data->x++;
	}
}

void	push_rays(t_ply *data, double rad)
{
	int	i;
	int	x;
	int	y;
	int	ox;
	int	oy;

	i = 0;
	y = data->o_y;
	x = data->o_x;
	while (i < data->len_ray)
	{
		ox = x - (i * cos(rad));
		oy = y - (i * sin(rad));
		my_mlx_pixel_put(data->data, ox, oy, 0x10FF0000);
		i++;
	}
}

void	fov_player(t_ply *data)
{
	double	rad;
	double	a;
	int		colomn;

	rad = deg_to_rad(data->angle);
	a = rad;
	colomn = 0;
	while (colomn < data->nb_rays)
	{
		push_rays(data, rad);
		colomn++;
		rad += 0.001;
	}
}
