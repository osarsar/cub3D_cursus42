/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 08:15:37 by osarsar           #+#    #+#             */
/*   Updated: 2023/09/16 00:09:30 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	put_player(t_ply *data)
{
	data->start_x = data->p_x - data->radius;
	data->end_x = data->p_x + data->radius;
	data->start_y = data->p_y - data->radius;
	data->end_y = data->p_y + data->radius;
	data->x = data->start_x;
	while (data->x <= data->end_x)
	{
		data->y = data->start_y;
		while (data->y <= data->end_y)
		{
			if (((data->x - data->p_x) * (data->x - data->p_x))
				+ ((data->y - data->p_y) * (data->y - data->p_y))
				<= (data->radius * data->radius))
				my_mlx_pixel_put(data->mydata, data->x, data->y, 0x00FF0000);
			data->y++;
		}
		data->x++;
	}
}

void	first_hori_verti(t_ply *data)
{
	data->first_hy = (data->p_y / 80) * 80;
	data->first_hx = (data->first_hy - data->p_y / tan(data->rad));
	data->first_vx = (data->p_x / 80) * 80;
	data->first_vy = ((data->first_vx - data->p_x) * tan(data->rad));
}

void	padding(t_ply *data)
{
	data->h_dy = 80;
	data->h_dx = data->h_dy / tan(data->rad);
	data->v_dx = 80;
	data->v_dy = data->v_dx * tan(data->rad);
}

void	init_angle(t_ply *data)
{
	data->rad = fmod(data->rad, (2 * M_PI));
	if (data->rad < 0)
		data->rad = (2 * M_PI) + data->rad;
}

void	fov_player(t_ply *data)
{
	char	*view;

	data->rad = deg_to_rad(data->angle);
	init_angle(data);
	view = check_view(data);
	first_hori_verti(data);
	padding(data);
	modify_depend_view(data, view);
	hori_wall_cord(data, view);
	verti_wall_cord(data, view);
	take_distance(data);
	push_rays(data);
}
