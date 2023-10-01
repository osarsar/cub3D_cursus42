/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stemsama <stemsama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 08:15:37 by osarsar           #+#    #+#             */
/*   Updated: 2023/10/01 17:54:01 by stemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	first_hori_verti(t_ply *data)
{
	data->first_hy = floor(data->p_y / NUM_PIXELS) * NUM_PIXELS;
	data->first_hx = ((data->first_hy - data->p_y / tan(data->fov)));
	data->first_vx = floor(data->p_x / NUM_PIXELS) * NUM_PIXELS;
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
		data->img = data->img_w;
	else if (data->check_h_v == 1)
		data->img = data->img_e;
	else if (data->check_h_v == 0
		&& (!ft_strcmp(view, "up_right") || !ft_strcmp(view, "up_left")))
		data->img = data->img_n;
	else
		data->img = data->img_s;
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
		init_angle_2pi(data);
		view = check_view(data);
		first_hori_verti(data);
		padding(data);
		modify_depend_view(data, view);
		hori_wall_cord(data, view);
		verti_wall_cord(data, view);
		take_distance(data);
		data->fov += rad / data->width_of_win;
		draw_map_3d(data, colomn);
		colomn++;
	}
}
