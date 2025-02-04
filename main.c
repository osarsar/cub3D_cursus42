/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stemsama <stemsama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 20:41:40 by osarsar           #+#    #+#             */
/*   Updated: 2023/09/29 15:38:46 by stemsama         ###   ########.fr       */
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
	data->speed = 7;
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

int	move_player(int key, t_ply *data)
{
	if (key == 53)
		exit(1);
	else if (data->k_right == 1)
		move_player_2(data, key);
	else if (data->k_left == 1)
		move_player_2(data, key);
	else if (data->k_down == 1)
		move_player_2(data, key);
	else if (data->k_up == 1)
		move_player_2(data, key);
	else if (data->tr_right)
		data->face_angle += 3;
	else if (data->tr_left)
		data->face_angle -= 3;
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
	data->img_n = ft_texture(data, data->no_path);
	data->img_s = ft_texture(data, data->so_path);
	data->img_w = ft_texture(data, data->we_path);
	data->img_e = ft_texture(data, data->ea_path);
	data->img = data->img_n;
	main_2(data);
	mlx_loop(data->mlx);
}
