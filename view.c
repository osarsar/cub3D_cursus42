/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 08:42:48 by osarsar           #+#    #+#             */
/*   Updated: 2023/09/28 14:43:16 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_angle(t_ply *data)
{
	data->face_rad = fmod(data->face_rad, (2 * M_PI));
	if (data->face_rad < 0)
		data->face_rad = (2 * M_PI) + data->face_rad;
}

void	init_angle_2pi(t_ply *data)
{
	data->fov = fmod(data->fov, (2 * M_PI));
	if (data->fov < 0)
		data->fov = (2 * M_PI) + data->fov;
}

void	view_to_start(t_ply *data)
{
	if (data->map[data->x][data->y] == 'N')
		data->face_angle = 90;
	else if (data->map[data->x][data->y] == 'S')
		data->face_angle = 270; 
	else if (data->map[data->x][data->y] == 'W')
		data->face_angle = 180; 
	else if (data->map[data->x][data->y] == 'E')
		data->face_angle = 0; 
}

double	init_rad(t_ply *data, double rad)
{
	data->face_rad = deg_to_rad(data->face_angle);
	init_angle(data);
	rad = deg_to_rad(data->angle);
	data->fov = data->face_rad - (rad / 2);
	return (rad);
}
