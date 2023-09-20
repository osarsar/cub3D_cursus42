/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stemsama <stemsama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 08:15:37 by osarsar           #+#    #+#             */
/*   Updated: 2023/09/20 18:32:22 by stemsama         ###   ########.fr       */
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
	data->first_hy = (data->p_y / NUM_PIXELS) * NUM_PIXELS;
	data->first_hx = (data->first_hy - data->p_y / tan(data->fov));
	data->first_vx = (data->p_x / NUM_PIXELS) * NUM_PIXELS;
	data->first_vy = ((data->first_vx - data->p_x) * tan(data->fov));
}

void	padding(t_ply *data)
{
	data->h_dy = NUM_PIXELS;
	data->h_dx = data->h_dy / tan(data->fov);
	data->v_dx = NUM_PIXELS;
	data->v_dy = data->v_dx * tan(data->fov);
}

int	get_ofset_colomn(t_ply *data)
{
	int		x;
	char	*view;

	x = 0;
	view = check_view(data);
	if (data->check_h_v == 0)
		x = fmod(data->x_wall, NUM_PIXELS);
	else if (data->check_h_v == 1)
		x = fmod(data->y_wall, NUM_PIXELS);
	if (data->check_h_v == 1
		&& (!ft_strcmp(view, "down_right") || !ft_strcmp(view, "up_left")))
		data->img = data->img_s;
	else if (data->check_h_v == 1)
		data->img = data->img_n;
	else if (data->check_h_v == 0
		&& (!ft_strcmp(view, "up_right") || !ft_strcmp(view, "up_left")))
		data->img = data->img_w;
	else
		data->img = data->img_e;
	return (x);
}

void	fov_player(t_ply *data)
{
	char	*view;
	int		colomn;
	double	rad;
	int		i;

	i = 0;
	colomn = 0;
	rad = 0;
	rad = init_rad(data, rad);
	while (colomn <= data->width_of_win)
	{
		draw_view(data);
		init_angle_2pi(data);
		view = check_view(data);
		first_hori_verti(data);
		padding(data);
		modify_depend_view(data, view);
		hori_wall_cord(data, view);
		verti_wall_cord(data, view);
		take_distance(data);
		push_rays(data);
		data->fov += rad / data->width_of_win;
		draw_map_3d(data, colomn);
		colomn++;
	}
}
