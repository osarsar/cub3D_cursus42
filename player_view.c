/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_view.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 22:44:41 by osarsar           #+#    #+#             */
/*   Updated: 2023/09/15 23:49:52 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char *check_view(double rad)
{
	if ((rad >= 0 && rad <= M_PI))
	{
		if (rad >= 0 && rad <= (0.5 * M_PI))
			return ("up_left");
		else
			return ("up_right");
	}
	else
	{
		if ((rad >= M_PI && rad <= (M_PI + (0.5 * M_PI))))
			return ("down_left");
		else
			return ("down_right");
	}
}

void	modify_depend_view(t_ply *data, char *view, double rad)
{
	if (!ft_strcmp(view, "up_left"))
	{
		data->first_hx = data->p_x - ((data->p_y - data->first_hy) / tan(rad));
		data->h_dx *= -1;
		data->h_dy *= -1;
		data->first_vy = data->p_y - ((data->p_x - data->first_vx) * tan(rad));
		data->v_dy *= -1;
		data->v_dx *= -1;
	}
	else if (!ft_strcmp(view, "up_right"))
	{
		data->first_hx = data->p_x - ((data->p_y - data->first_hy) / tan(rad));
		data->h_dx *= -1;
		data->h_dy *= -1;
		data->first_vx += 80;
		data->first_vy = data->p_y + ((data->first_vx - data->p_x) * tan(rad));
	}
	else if (!ft_strcmp(view, "down_left"))
	{
		data->first_hy += 80;
		data->first_hx = data->p_x - ((data->p_y - data->first_hy) / tan(rad));
		data->first_vx += 80;
		data->first_vy = data->p_y - ((data->p_x - data->first_vx) * tan(rad));
	}
	else if (!ft_strcmp(view, "down_right"))
	{
		data->first_hy += 80;
		data->first_hx = data->p_x - ((data->p_y - data->first_hy) / tan(rad));
		data->first_vy = data->p_y + ((data->first_vx - data->p_x) * tan(rad));
		data->v_dy *= -1;
		data->v_dx *= -1;
	}
}

void	hori_wall_cord(t_ply *data, char *view)
{
	data->xstep = data->first_vx;
	data->ystep = data->first_vy;
	if (!ft_strcmp(view, "up_left") || !ft_strcmp(view, "down_right"))
		data->xstep--;
	while (data->xstep > 0 && data->ystep > 0 && data->ystep < 1040 && data->xstep < 1040)
	{
		if (data->map[((int)data->ystep / 80)][((int)data->xstep / 80)] == '1')
			break;
		data->xstep += data->v_dx;
		data->ystep += data->v_dy;
	}
	data->vx_wall = data->xstep;
	data->vy_wall = data->ystep;
}

void	verti_wall_cord(t_ply *data, char *view)
{
	data->xstep = data->first_hx;
	data->ystep = data->first_hy;
	if (!ft_strcmp(view, "up_left") || !ft_strcmp(view, "up_right"))
		data->ystep--;
	while (data->xstep > 0 && data->ystep > 0 && data->ystep < 1040 && data->xstep < 1040)
	{
		if (data->map[(int)data->ystep / 80][(int)data->xstep / 80] == '1')
			break;
		data->xstep += data->h_dx;
		data->ystep += data->h_dy;
	}
	data->hx_wall = data->xstep;
	data->hy_wall = data->ystep;
}

void	take_distance(t_ply *data)
{
	double x;
	double y;

	x = (data->p_x - data->hx_wall) * (data->p_x - data->hx_wall);
	y = (data->p_y - data->hy_wall) * (data->p_y - data->hy_wall);
	data->h_distance = sqrt(x + y);
	x = (data->p_x - data->vx_wall) * (data->p_x - data->vx_wall);
	y = (data->p_y - data->vy_wall) * (data->p_y - data->vy_wall);
	data->v_distance = sqrt(x + y);
	if (data->h_distance <= data->v_distance)
		data->len_ray = data->h_distance;
	else
		data->len_ray = data->v_distance;
}
void	push_rays(t_ply *data, double rad)
{
	int i = 0;
	int	ox;
	int	oy;

	while (i <= data->len_ray)
	{
		ox = data->p_x - (i * cos(rad));
		oy = data->p_y - (i * sin(rad));
		my_mlx_pixel_put(data->mydata, ox, oy, 0x00FF0000);
		i++;
	}

}
