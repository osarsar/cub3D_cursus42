/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_view.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stemsama <stemsama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 22:44:41 by osarsar           #+#    #+#             */
/*   Updated: 2023/09/18 23:17:04 by stemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*check_view_player(t_ply *data)
{
	if ((data->face_rad >= 0 && data->face_rad <= M_PI))
	{
		if (data->face_rad >= 0 && data->face_rad <= (0.5 * M_PI))
			return ("up_left");
		else
			return ("up_right");
	}
	else
	{
		if ((data->face_rad >= M_PI && data->face_rad <= (M_PI + (0.5 * M_PI))))
			return ("down_left");
		else
			return ("down_right");
	}
}

char	*check_view(t_ply *data)
{
	if ((data->fov >= 0 && data->fov <= M_PI))
	{
		if (data->fov >= 0 && data->fov <= (0.5 * M_PI))
			return ("up_left");
		else
			return ("up_right");
	}
	else
	{
		if ((data->fov >= M_PI && data->fov <= (M_PI + (0.5 * M_PI))))
			return ("down_left");
		else
			return ("down_right");
	}
}

void	verti_wall_cord(t_ply *data, char *view)
{
	int	x;
	int	y;

	data->xstep = data->first_vx;
	data->ystep = data->first_vy;
	if (!ft_strcmp(view, "up_left") || !ft_strcmp(view, "down_right"))
		data->xstep--;
	while (data->xstep > 0 && data->ystep > 0
		&& data->ystep < data->height_of_win
		&& data->xstep < data->width_of_win)
	{
		x = data->ystep / NUM_PIXELS;
		y = data->xstep / NUM_PIXELS;
		if (data->map[x][y] == '1')
			break ;
		data->xstep += data->v_dx;
		data->ystep += data->v_dy;
	}
	data->vx_wall = data->xstep;
	data->vy_wall = data->ystep;
}

void	hori_wall_cord(t_ply *data, char *view)
{
	int	x;
	int	y;

	data->xstep = data->first_hx;
	data->ystep = data->first_hy;
	if (!ft_strcmp(view, "up_left") || !ft_strcmp(view, "up_right"))
		data->ystep--;
	while (data->xstep > 0 && data->ystep > 0
		&& data->ystep < data->height_of_win 
		&& data->xstep < data->width_of_win)
	{
		x = data->ystep / NUM_PIXELS;
		y = data->xstep / NUM_PIXELS;
		if (data->map[x][y] == '1')
			break ;
		data->xstep += data->h_dx;
		data->ystep += data->h_dy;
	}
	data->hx_wall = data->xstep;
	data->hy_wall = data->ystep;
}

void	take_distance(t_ply *data)
{
	double	x;
	double	y;

	x = (data->p_x - data->hx_wall) * (data->p_x - data->hx_wall);
	y = (data->p_y - data->hy_wall) * (data->p_y - data->hy_wall);
	data->h_distance = sqrt(x + y);
	x = (data->p_x - data->vx_wall) * (data->p_x - data->vx_wall);
	y = (data->p_y - data->vy_wall) * (data->p_y - data->vy_wall);
	data->v_distance = sqrt(x + y);
	if (data->h_distance <= data->v_distance)
	{
		data->len_ray = data->h_distance;
		data->x_wall = data->hx_wall;
		data->y_wall = data->hy_wall;
		data->check_h_v = 0;
	}
	else
	{
		data->len_ray = data->v_distance;
		data->x_wall = data->vx_wall;
		data->y_wall = data->vy_wall;
		data->check_h_v = 1;
	}
	if (data->len_ray == 0)
		data->len_ray = 1;
}
