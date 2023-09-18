/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stemsama <stemsama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 08:15:37 by osarsar           #+#    #+#             */
/*   Updated: 2023/09/18 05:42:51 by stemsama         ###   ########.fr       */
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

int get_ofset_colomn(t_ply *data)
{
	int	x = 0;

	if (data->check_h_v == 0)
		x = (data->x_wall/80 - (int)data->x_wall/80) * 80;
	else if (data->check_h_v == 1)
		x = (data->y_wall/80 - (int)data->y_wall/80) * 80;
	// printf("data->check_h_v = %d\n", data->check_h_v);
	// printf("data->x_wall = %f\n", data->y_wall);
	// printf("data->y_wall = %d\n", (int)data->y_wall);
	// printf("x = %d\n", x);
	return (x);
}

void draw_map_3d(t_ply *data, int colomn)
{
	int 	wall_height;
	int 	start_wall;
	int 	end_wall;
	int 	line;
	int		x;
	int		y;
	int		color;

	// wall_height = (data->width_f_wall * NUM_PIXELS) / (data->len_ray * cos(data->fov));//(data->height_of_win * NUM_PIXELS)
	wall_height = (data->width_f_wall * NUM_PIXELS) / (data->len_ray);//(data->height_of_win * NUM_PIXELS)
	// wall_height = wall_height / data->len_ray * cos(data->fov);//(data->height_of_win * NUM_PIXELS)
	// wall_height = wall_height * ((data->width_f_wall / 2) * tan(deg_to_rad(60) / 2));//(data->height_of_win * NUM_PIXELS)
	start_wall = (data->height_f_wall / 2) - (wall_height / 2);
	x = get_ofset_colomn(data);
	if (start_wall <= 0)
		start_wall = 0;
	end_wall = (data->height_f_wall / 2) + (wall_height / 2);
	if (end_wall >= data->height_f_wall)
		end_wall = data->height_f_wall;
	line = 0;
	while (line < data->height_f_wall)
	{
		if (line < start_wall)
			color = to_rgb(data->c_1, data->c_2, data->c_3);
		else if ((line >= start_wall) && (line <= end_wall))
		{
			y = (line - start_wall) * (NUM_PIXELS / data->height_f_wall);
			color = data->tab_color[(NUM_PIXELS * y) + x];
		}
		else if (line > end_wall)
			color = to_rgb(data->f_1, data->f_2, data->f_3);
		my_mlx_pixel_put(data->mydata, colomn, line, color);
		line++;
	}
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
	while (colomn <= data->width_f_wall)
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
		data->fov += rad / data->width_f_wall;
		draw_map_3d(data, colomn);
		colomn++;
	}
}
