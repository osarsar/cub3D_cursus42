/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 08:15:37 by osarsar           #+#    #+#             */
/*   Updated: 2023/09/17 08:02:10 by osarsar          ###   ########.fr       */
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

void	init_angle(t_ply *data)
{
	data->face_rad = fmod(data->face_rad, (2 * M_PI));
	if (data->face_rad < 0)
		data->face_rad = (2 * M_PI) + data->face_rad;
}

void draw_map_3d(t_ply *data, int colomn)
{
	int wall_height;
	int start_wall;
	int end_wall;
	int line;

	wall_height = (data->width_f_wall * 80) / data->len_ray;//(data->height_of_win * NUM_PIXELS)
	start_wall = (data->height_f_wall / 2) - (wall_height / 2);
	if (start_wall <= 0)
		start_wall = 0;
	end_wall = (data->height_f_wall / 2) + (wall_height / 2);
	if (end_wall >= data->height_f_wall)
		end_wall = data->height_f_wall;
	line = 0;
	while (line < data->height_f_wall)
	{
		if (line < start_wall)
			my_mlx_pixel_put(data->mydata, colomn, line, 0xAABBFF);
		else if ((line >= start_wall) && (line <= end_wall))
			my_mlx_pixel_put(data->mydata, colomn, line, 0xFFA500);
		else if (line > end_wall)
			my_mlx_pixel_put(data->mydata, colomn, line, 0x00FF00);
		line++;
	}
}
void	init_angle_2pi(t_ply *data)
{
	data->fov = fmod(data->fov, (2 * M_PI));
	if (data->fov < 0)
		data->fov = (2 * M_PI) + data->fov;
}

void	fov_player(t_ply *data)
{
	char	*view;
	int		colomn;
	double	rad;
	int		i;

	i = 0;
	colomn = 0;
	data->face_rad = deg_to_rad(data->face_angle);
	init_angle(data);
	rad = deg_to_rad(data->angle);
	data->rad = data->face_rad - (rad / 2);
	data->fov = data->rad;
	while (colomn <= 200)
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
		data->fov += rad / 200;
		draw_map_3d(data, colomn);
		colomn++;
	}
}

void	draw_view(t_ply *data)
{
	int j = 0;
	while (j <= 50)
	{
		int ox = data->p_x - (j * cos(data->face_rad));
		int oy = data->p_y - (j * sin(data->face_rad));
		my_mlx_pixel_put(data->mydata, ox, oy, 0x0000FF);
		j++;
	}	
}
