/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 20:41:40 by osarsar           #+#    #+#             */
/*   Updated: 2023/09/15 12:34:29 by osarsar          ###   ########.fr       */
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
	data->nb_x = 80;
	data->nb_y = 80;
	data->speed = 20;
	data->map = NULL;
	data->start_j = 0;
	data->radius = 7;
	data->start_x = data->p_x - data->radius;
	data->end_x = data->p_x + data->radius;
	data->start_y = data->p_y - data->radius;
	data->end_y = data->p_y + data->radius;
	data->nb_rays = 1000;
	data->len_ray = 400;
	data->angle = 60;
}

void	collect_map(t_ply *data)
{
	char	*line;
	char	*join_lines;
	int		fd;

	join_lines = NULL;
	fd = open("map.cub", O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		join_lines = ft_strjoin(join_lines, line);
		free(line);
		line = get_next_line(fd);
	}
	data->map = ft_split(join_lines, '\n');
}

double	deg_to_rad(double deg)
{
	return (deg * (M_PI / 180));
}

int	move_player(int key, t_ply *data)
{
	if (key == 53)
		exit(1);
	else if (key == 2)
		data->p_x += 1 * data->speed;
	else if (key == 0)
		data->p_x += -1 * data->speed;
	else if (key == 1)
		data->p_y += 1 * data->speed;
	else if (key == 13)
		data->p_y += -1 * data->speed;
	else if (key == 124)
		data->angle += 5;
	else if (key == 123)
		data->angle -= 5;
	return (0);
}

int	main(int ac, char **av)
{
	t_ply	*data;

	data = malloc(sizeof(t_ply));
	if (!data)
		return (0);
	data->mydata = malloc(sizeof(t_data));
	if (!data->mydata)
	{
		free(data);
		return (0);
	}
	init_data(data, ac, av);
	collect_map(data);
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, 1040, 1040, "Hello world!");
	data->mydata->img = mlx_new_image(data->mlx, 1050, 1050);
	data->mydata->addr = mlx_get_data_addr(data->mydata->img, 
			&data->mydata->bits_per_pixel, 
			&data->mydata->line_length, &data->mydata->endian);
	mlx_loop_hook (data->mlx, &creat_map, data);
	mlx_hook (data->win, 2, 0, &move_player, data);
	mlx_loop(data->mlx);
}
