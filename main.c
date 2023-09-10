/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 20:41:40 by osarsar           #+#    #+#             */
/*   Updated: 2023/09/10 03:01:46 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	init_data(t_ply *data, int ac, char **av)
{
	data->ac = ac;
	data->av = av;
	data->map = 0;
	data->x = 0;
	data->y = 0;
	data->o_x = 0;
	data->o_y = 0;
	data->nb_x = 80;
	data->nb_y = 80;
	data->speed = 15;
	data->map = NULL;
	data->start_j = 0;
	data->radius = 7;
	data->start_x = data->o_x - data->radius;
	data->end_x = data->o_x + data->radius;
	data->start_y = data->o_y - data->radius;
	data->end_y = data->o_y + data->radius;
	data->nb_rays = 320;
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
	return (deg * (M_PI / 180.0));
}

void	creat_map_line(t_ply *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	data->y = 0;
	while (data->map[data->x][data->y])
	{
		while (i < data->nb_x)
		{
			j = data->start_j;
			while (j < data->nb_y)
			{
				if (data->map[data->x][data->y] == '1')
					my_mlx_pixel_put(data->data, i, j, 0x808080);
				else if (data->map[data->x][data->y] == '0')
					my_mlx_pixel_put(data->data, i, j, 0x00FFFFFF);
				else if (data->map[data->x][data->y] == 'N')
				{
					my_mlx_pixel_put(data->data, i, j, 0x00FFFFFF);
					if (data->o_x == 0 && data->o_y == 0)
					{
						data->o_x = i + (80 / 2);
						data->o_y = j + (80 / 2);
					}
				}
				j++;
			}
			i++;
		}
		data->y++;
		data->nb_x += 80;
	}
}

void	push_rays(t_ply *data, double rad)
{
	int	i;
	int	x;
	int	y;
	int	ox;
	int	oy;

	i = 0;
	y = data->o_y;
	x = data->o_x;
	while (i < 100)
	{
		ox = x - (i * cos(rad));
		oy = y - (i * sin(rad));
		my_mlx_pixel_put(data->data, ox, oy, 0x00FF0000);
		i++;
	}
}

void	fov_player(t_ply *data)
{
	double	angle;
	double	rad;
	double	a;
	int		colomn;

	angle = 30;
	rad = deg_to_rad(angle);
	a = rad;
	colomn = 0;
	while (colomn < data->nb_rays)
	{
		push_rays(data, rad);
		colomn++;
		rad += a / 100;
	}
}

void	put_player(t_ply *data)
{
	int	x;
	int	y;

	data->start_x = data->o_x - data->radius;
	data->end_x = data->o_x + data->radius;
	data->start_y = data->o_y - data->radius;
	data->end_y = data->o_y + data->radius;
	data->x = data->start_x;
	while (data->x <= data->end_x)
	{
		data->y = data->start_y;
		while (data->y <= data->end_y)
		{
			if (((data->x - data->o_x) * (data->x - data->o_x))
				+ ((data->y - data->o_y) * (data->y - data->o_y))
				<= (data->radius * data->radius))
					my_mlx_pixel_put(data->data, data->x, data->y, 0x00FF0000);
			data->y++;
		}
		data->x++;
	}
}

int	creat_map(t_ply *data)
{
	data->x = 0;
	data->nb_y = 80;
	data->start_j = 0;
	while (data->map[data->x])
	{
		data->y = 0;
		data->nb_x = 80;
		creat_map_line(data);
		data->nb_y += 80;
		data->start_j += 80;
		data->x++;
	}
	put_player(data);
	mlx_put_image_to_window(data->mlx, data->win, data->data->img, 0, 0);
	fov_player(data);
	return (0);
}

int	move_player(int key, t_ply *data)
{
	if (key == 53)
		exit(1);
	if (key == 2)
	{
			data->o_x += +1 * data->speed;
		return(0);
	}
	if (key == 0)
	{
			data->o_x += -1 * data->speed;
		return(0);
	}
	if (key == 1)
	{
			data->o_y += +1 * data->speed;
		return(0);
	}
	if (key == 13)
	{
			data->o_y += -1 * data->speed;
		return(0);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_ply	*data;

	data = malloc(sizeof(t_ply));
	if (!data)
		return (0);
	data->data = malloc(sizeof(t_data));
	if (!data->data)
	{
		free(data);
		return (0);
	}
	init_data(data, ac, av);
	collect_map(data);
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, 1040, 1040, "Hello world!");
	data->data->img = mlx_new_image(data->mlx, 1050, 1050);// a revoir
	data->data->addr = mlx_get_data_addr(data->data->img, &data->data->bits_per_pixel, &data->data->line_length, &data->data->endian);
	mlx_loop_hook (data->mlx, &creat_map, data);
	mlx_hook (data->win, 2, 0, &move_player, data);
	mlx_loop(data->mlx);
}
