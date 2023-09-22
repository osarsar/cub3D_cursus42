/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stemsama <stemsama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:29:54 by stemsama          #+#    #+#             */
/*   Updated: 2023/09/22 23:14:05 by stemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	close_win(t_ply *data)
{
	mlx_destroy_window(data->mlx, data->win);
	exit(0);
	return (0);
}

void	move_player_2_a(t_ply *data, int key, char *view)
{
	if (key == UP)
		move_player_2_up(data, view);
	else if (key == DOWN)
		move_player_2_do(data, view);
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
}

void	move_player_2_b(t_ply *data, int x_tmp, int y_tmp)
{
	int		x;
	int		y;

	x = (int)(data->p_x / NUM_PIXELS);
	y = (int)(data->p_y / NUM_PIXELS);
	if (data->map[(int)((data->p_y - 7) / NUM_PIXELS)][x] == '1'
		|| data->map[(int)((data->p_y + 7) / NUM_PIXELS)][x] == '1'
		|| data->map[y][(int)((data->p_x - 10) / NUM_PIXELS)] == '1'
		|| data->map[y][(int)((data->p_x + 8) / NUM_PIXELS)] == '1')
	{
		data->p_x = x_tmp;
		data->p_y = y_tmp;
	}
	if ((x < 0 || y < 0
			|| x >= ((data->width_of_win / NUM_PIXELS) - 1)
			|| y >= ((data->height_of_win / NUM_PIXELS) - 1)
			|| data->map[y][x] == '1')
			|| (data->map[y][(int)(x_tmp / NUM_PIXELS)] == '1'
		&& data->map[(int)(y_tmp / NUM_PIXELS)][x] == '1'))
	{
		data->p_x = x_tmp;
		data->p_y = y_tmp;
	}
}

int	cal_str_wall(int h_win, int h_wall)
{
	int	start_of_wall;

	start_of_wall = (h_win / 2) - (h_wall / 2);
	if (start_of_wall <= 0)
		start_of_wall = 0;
	return (start_of_wall);
}

int	cal_end_wall(int h_win, int h_wall)
{
	int	end_of_wall;

	end_of_wall = (h_win / 2) + (h_wall / 2);
	if (end_of_wall >= h_win)
		end_of_wall = h_win;
	return (end_of_wall);
}

// void is_pre()
// {}

// void is_rel()
// {}
