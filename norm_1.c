/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stemsama <stemsama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 23:31:13 by stemsama          #+#    #+#             */
/*   Updated: 2023/09/19 19:07:30 by stemsama         ###   ########.fr       */
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
	int	wall_height;
	int	start_wall;
	int	end_wall;
	int	line;
	int	x_y_cl[3];

	data->len_ray = data->len_ray * cos(data->fov - data->face_rad);
	wall_height = (data->width_of_win * NUM_PIXELS) / ((data->len_ray));
	start_wall = (data->height_of_win / 2) - (wall_height / 2);
	x_y_cl[0] = get_ofset_colomn(data);
	if (start_wall <= 0)
		start_wall = 0;
	end_wall = (data->height_of_win / 2) + (wall_height / 2);
	if (end_wall >= data->height_of_win)
		end_wall = data->height_of_win;
	line = 0;
	while (line < data->height_of_win)
	{
		if (line < start_wall)
			x_y_cl[2] = to_rgb(data->c_1, data->c_2, data->c_3);
		else if ((line >= start_wall) && (line <= end_wall))
		{
			x_y_cl[1] = (line - start_wall);
			x_y_cl[1] = x_y_cl[1] * ((double)NUM_PIXELS / wall_height);
			x_y_cl[2] = data->tab_color[(NUM_PIXELS * x_y_cl[1]) + x_y_cl[0]];
		}
		else if (line > end_wall)
			x_y_cl[2] = to_rgb(data->f_1, data->f_2, data->f_3);
		my_mlx_pixel_put(data->mydata, colomn, line, x_y_cl[2]);
		line++;
	}
}

int	move_player_2(t_ply *data, int key)
{
	int		x;
	int		y;
	int		x_tmp;
	int		y_tmp;
	char	*view;

	x_tmp = data->p_x;
	y_tmp = data->p_y;
	view = check_view_player(data);
	printf("key = %d\n", key);
	if (key == UP)
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
	else if (key == DOWN)
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
	else if (key == RIGHT)
	{
		data->p_x -= cos(data->face_rad + (M_PI * 0.5)) * data->speed;
		data->p_y -= sin(data->face_rad + (M_PI * 0.5)) * data->speed;
	}
	else if (key == LEFT)
	{
		data->p_x += cos(data->face_rad + (M_PI * 0.5)) * data->speed;
		data->p_y += sin(data->face_rad + (M_PI * 0.5)) * data->speed;
	}
	x = (int)(data->p_x / NUM_PIXELS);
	y = (int)(data->p_y / NUM_PIXELS);
	printf("data->p_y %d\n", y);
	if ((x < 0 || y < 0
			|| x >= ((data->width_of_win / NUM_PIXELS) - 1)
			|| y >= ((data->height_of_win / NUM_PIXELS) - 1)
			|| data->map[y][x] == '1')
			|| (data->map[y][(int)(x_tmp / NUM_PIXELS)] == '1'
		&& data->map[(int)(y_tmp / NUM_PIXELS)][x] == '1'))
	{
		printf("-->::\n\n");
		data->p_x = x_tmp;
		data->p_y = y_tmp;
		printf("data->map[y][x] = %c\n", data->map[y][x]);
	}
	return (0);
}
