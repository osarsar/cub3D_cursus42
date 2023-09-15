/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 08:15:37 by osarsar           #+#    #+#             */
/*   Updated: 2023/09/15 23:48:36 by osarsar          ###   ########.fr       */
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

void	first_hori_verti(t_ply *data, double rad)
{
	data->first_hy = (data->p_y / 80) * 80;
	data->first_hx = (data->first_hy - data->p_y / tan(rad));
	data->first_vx = (data->p_x / 80) * 80;
	data->first_vy = ((data->first_vx - data->p_x) * tan(rad));
}

void	padding(t_ply *data, double rad)
{
	data->h_dy = 80;
	data->h_dx = data->h_dy / tan(rad);
	data->v_dx = 80;
	data->v_dy = data->v_dx * tan(rad);
}

void	init_angle(double *rad)
{
	*rad = fmod(*rad, (2 * M_PI));
	if (*rad < 0)
		*rad = (2 * M_PI) + *rad;
}

void	fov_player(t_ply *data)
{
	double	rad;
	char	*view;

	rad = deg_to_rad(data->angle);
	init_angle(&rad);
	view = check_view(rad);
	first_hori_verti(data, rad);
	padding(data, rad);
	modify_depend_view(data, view, rad);
	hori_wall_cord(data, view);
	verti_wall_cord(data, view);
	take_distance(data);
	push_rays(data, rad);
}
