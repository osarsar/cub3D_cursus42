/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stemsama <stemsama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 20:41:40 by osarsar           #+#    #+#             */
/*   Updated: 2023/09/18 23:44:01 by stemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_data(t_ply *data, int ac, char **av)
{
	data->ac = ac;
	data->av = av;
	data->map = 0;
	data->x = 0;
	data->y = 0;
	data->p_x = 0;
	data->p_y = 0;
	data->nb_x = NUM_PIXELS;
	data->nb_y = NUM_PIXELS;
	data->speed = 10;
	data->map = NULL;
	data->start_j = 0;
	data->radius = 7;
	data->start_x = data->p_x - data->radius;
	data->end_x = data->p_x + data->radius;
	data->start_y = data->p_y - data->radius;
	data->end_y = data->p_y + data->radius;
	data->nb_rays = 1000;
	data->angle = 60;
}

double	deg_to_rad(double deg)
{
	return (deg * (M_PI / 180));
}

void	push_rays(t_ply *data)
{
	int	i;
	int	ox;
	int	oy;

	i = 0;
	while (i <= data->len_ray)
	{
		ox = data->p_x - (i * cos(data->fov));
		oy = data->p_y - (i * sin(data->fov));
		my_mlx_pixel_put(data->mydata, ox, oy, 0x00FF0000);
		i++;
	}
}

int	move_player(int key, t_ply *data)
{
	if (key == 53)
		exit(1);
	else if (key == RIGHT)
		move_player_2(data, key);
	else if (key == LEFT)
	{
		printf("LEFT\n");
		move_player_2(data, key);
	}
	else if (key == DOWN)
	{
		printf("DOWN\n");
		move_player_2(data, key);
	}
	else if (key == UP)
	{
		printf("up\n");
		move_player_2(data, key);
	}
	else if (key == 124)
		data->face_angle += 5;
	else if (key == 123)
		data->face_angle -= 5;
	return (0);
}

int	main(int ac, char **av)
{
	t_ply	*data;

	data = malloc(sizeof(t_ply));
	if (!data)
		affiche_er(2);
	data->mydata = malloc(sizeof(t_data));
	if (!data->mydata)
	{
		free(data);
		affiche_er(2);
	}
	init_data(data, ac, av);
	pars(data, ac, av);
	data->mlx = mlx_init();
	ft_texture(data);
	data->win = mlx_new_window(data->mlx, data->width_of_win,
			data->height_of_win, "3D_game");
	data->mydata->img = mlx_new_image(data->mlx,
			data->width_of_win + 1, data->height_of_win + 1);
	data->mydata->addr = mlx_get_data_addr(data->mydata->img, 
			&data->mydata->bits_per_pixel, 
			&data->mydata->line_length, &data->mydata->endian);
	mlx_loop_hook(data->mlx, &creat_map, data);
	mlx_hook(data->win, 2, 0, &move_player, data);
	mlx_loop(data->mlx);
}
