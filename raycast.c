/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:45:54 by osarsar           #+#    #+#             */
/*   Updated: 2023/09/18 22:40:39 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	raycast_up_left(t_ply *data)
{
	data->first_hx = data->p_x 
		- ((data->p_y - data->first_hy) / tan(data->fov));
	data->h_dx *= -1;
	data->h_dy *= -1;
	data->first_vy = data->p_y
		- ((data->p_x - data->first_vx) * tan(data->fov));
	data->v_dy *= -1;
	data->v_dx *= -1;
}

void	raycast_up_right(t_ply *data)
{
	data->first_hx = data->p_x 
		- ((data->p_y - data->first_hy) / tan(data->fov));
	data->h_dx *= -1;
	data->h_dy *= -1;
	data->first_vx += NUM_PIXELS;
	data->first_vy = data->p_y 
		+ ((data->first_vx - data->p_x) * tan(data->fov));
}

void	raycast_down_left(t_ply *data)
{
	data->first_hy += NUM_PIXELS;
	data->first_hx = data->p_x 
		- ((data->p_y - data->first_hy) / tan(data->fov));
	data->first_vx += NUM_PIXELS;
	data->first_vy = data->p_y 
		- ((data->p_x - data->first_vx) * tan(data->fov));
}

void	raycast_down_right(t_ply *data)
{
	data->first_hy += NUM_PIXELS;
	data->first_hx = data->p_x 
		- ((data->p_y - data->first_hy) / tan(data->fov));
	data->first_vy = data->p_y 
		+ ((data->first_vx - data->p_x) * tan(data->fov));
	data->v_dy *= -1;
	data->v_dx *= -1;
}

void	modify_depend_view(t_ply *data, char *view)
{
	if (!ft_strcmp(view, "up_left"))
		raycast_up_left(data);
	else if (!ft_strcmp(view, "up_right"))
		raycast_up_right(data);
	else if (!ft_strcmp(view, "down_left"))
		raycast_down_left(data);
	else if (!ft_strcmp(view, "down_right"))
		raycast_down_right(data);
}
