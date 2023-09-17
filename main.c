/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 20:41:40 by osarsar           #+#    #+#             */
/*   Updated: 2023/09/17 04:52:28 by osarsar          ###   ########.fr       */
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
	data->face_angle = 90;
	data->angle = 60;
}

double	deg_to_rad(double deg)
{
	return (deg * (M_PI / 180));
}
//123 left
//124 right
int	move_player_2(t_ply *data, int key)
{
	// int		x;
	// int		y;
	int		x_tmp;
	int		y_tmp;

	x_tmp = data->p_x;
	y_tmp = data->p_y;
	//new position x and y
	printf("key = %d\n", key);
	if (key == RIGHT)
	{
		printf("up\n");
		data->p_x += cos(data->face_angle) * data->speed;
		data->p_y += sin(data->face_angle) * data->speed;
	}
	else if (key == LEFT)
	{
		printf("down\n");
		data->p_x -= cos(data->face_angle) * data->speed;
		data->p_y -= sin(data->face_angle) * data->speed;
	}
	else if (key == DOWN)
	{
		printf("right\n");
		data->p_x -= cos(M_PI - data->face_angle) * data->speed;
		data->p_y += sin(M_PI - data->face_angle) * data->speed;
	}
	else if (key == UP)
	{
		printf("left\n");
		data->p_x += cos(M_PI - data->face_angle) * data->speed;
		data->p_y -= sin(M_PI - data->face_angle) * data->speed;
	}
	//check wall
	// x = (int)(data->p_x / NUM_PIXELS);
	// y = (int)(data->p_y / NUM_PIXELS);
	// printf("data->p_y %d\n", y);
	// if (x < 0 || y < 0
	// 	|| x >= ((data->width_f_wall / NUM_PIXELS) - 1) || y >= ((data->height_f_wall / NUM_PIXELS) - 1)
	// 	|| data->map[y][x] == '1')
	// {
	// 	printf("-->::\n\n");
	// 	data->p_x = x_tmp;
	// 	data->p_y = y_tmp;
	// 	printf("data->map[y][x] = %c\n", data->map[y][x]);
	// }
	return (0);
}
//13 - up
//1 - down
//2 - right
//0 - left
int	move_player(int key, t_ply *data)
{
	if (key == 53)
		exit(1);
	else if (key == RIGHT)
		data->p_x +=1 * data->speed;
		//move_player_2(data, key);
	else if (key == LEFT)
		data->p_x -=1 * data->speed;
		//move_player_2(data, key);
	else if (key == DOWN)
		data->p_y +=1 * data->speed;
		//move_player_2(data, key);
	else if (key == UP)
		data->p_y -=1 * data->speed;
		//move_player_2(data, key);
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
	data->win = mlx_new_window(data->mlx, data->width_f_wall, data->height_f_wall, "Hello world!");
	data->mydata->img = mlx_new_image(data->mlx, data->width_f_wall + 1, data->height_f_wall + 1);
	data->mydata->addr = mlx_get_data_addr(data->mydata->img, 
			&data->mydata->bits_per_pixel, 
			&data->mydata->line_length, &data->mydata->endian);
	mlx_loop_hook(data->mlx, &creat_map, data);
	mlx_hook(data->win, 2, 0, &move_player, data);
	mlx_loop(data->mlx);
}
