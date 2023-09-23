/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 23:31:13 by stemsama          #+#    #+#             */
/*   Updated: 2023/09/23 19:57:11 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_color(char **list_color, int i)
{
	free(list_color[i - 1]);
	free(list_color[i - 2]);
	free(list_color[i - 3]);
	free(list_color);
}

void	draw_map_3d(t_ply *data, int colomn)
{
	int	s_e_h_wall[3];
	int	x_y_cl[3];
	int	line;

	data->len_ray = data->len_ray * cos(data->fov - data->face_rad);
	s_e_h_wall[2] = (data->width_of_win * NUM_PIXELS) / ((data->len_ray));
	s_e_h_wall[0] = cal_str_wall(data->height_of_win, s_e_h_wall[2]);
	s_e_h_wall[1] = cal_end_wall(data->height_of_win, s_e_h_wall[2]);
	x_y_cl[0] = get_ofset_colomn(data);
	line = -1;
	while (++line < data->height_of_win - 1)
	{
		if (line < s_e_h_wall[0])
			x_y_cl[2] = to_rgb(data->c_1, data->c_2, data->c_3);
		else if ((line >= s_e_h_wall[0]) && (line <= s_e_h_wall[1] - 1))
		{
			x_y_cl[1] = line + (s_e_h_wall[2] / 2) - (data->height_of_win / 2);
			x_y_cl[1] = x_y_cl[1] * ((double)NUM_PIXELS / s_e_h_wall[2]);
			x_y_cl[2] = data->img->tab_color[(NUM_PIXELS * x_y_cl[1])
				+ x_y_cl[0]];
		}
		else if (line > s_e_h_wall[1])
			x_y_cl[2] = to_rgb(data->f_1, data->f_2, data->f_3);
		my_mlx_pixel_put(data->mydata, colomn, line, x_y_cl[2]);
	}
}

void	move_player_2_up(t_ply *data, char *view)
{
	if (!ft_strcmp(view, "up_right"))
	{
		data->p_x += cos(M_PI - data->face_rad) * data->speed;
		data->p_y -= sin(M_PI - data->face_rad) * data->speed;
	}
	if (!ft_strcmp(view, "up_left"))
	{
		data->p_x += cos(M_PI - data->face_rad) * data->speed;
		data->p_y -= sin(M_PI - data->face_rad) * data->speed;
	}
	if (!ft_strcmp(view, "down_right"))
	{
		data->p_x += cos(data->face_rad - M_PI) * data->speed;
		data->p_y += sin(data->face_rad - M_PI) * data->speed;
	}
	if (!ft_strcmp(view, "down_left"))
	{
		data->p_x += cos(data->face_rad - M_PI) * data->speed;
		data->p_y += sin(data->face_rad - M_PI) * data->speed;
	}
}

void	move_player_2_do(t_ply *data, char *view)
{
	if (!ft_strcmp(view, "up_right"))
	{
		data->p_x += cos(data->face_rad) * data->speed;
		data->p_y += sin(data->face_rad) * data->speed;
	}
	if (!ft_strcmp(view, "up_left"))
	{
		data->p_x += cos(data->face_rad) * data->speed;
		data->p_y += sin(data->face_rad) * data->speed;
	}
	if (!ft_strcmp(view, "down_right"))
	{
		data->p_x -= cos(data->face_rad - M_PI) * data->speed;
		data->p_y -= sin(data->face_rad - M_PI) * data->speed;
	}
	if (!ft_strcmp(view, "down_left"))
	{
		data->p_x -= M_PI + cos(data->face_rad - M_PI) * data->speed;
		data->p_y -= M_PI + sin(data->face_rad - M_PI) * data->speed;
	}
}

int	move_player_2(t_ply *data, int key)
{
	int		x_tmp;
	int		y_tmp;
	char	*view;

	x_tmp = data->p_x;
	y_tmp = data->p_y;
	view = check_view_player(data);
	move_player_2_a(data, key, view);
	move_player_2_b(data, x_tmp, y_tmp);
	return (0);
}
