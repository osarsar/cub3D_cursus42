/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 20:41:40 by osarsar           #+#    #+#             */
/*   Updated: 2023/09/04 10:31:10 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_data(t_data *data, int ac, char **av)
{
	data->ac = ac;
	data->av = av;
	data->map = 0;
	data->x = 0;
	data->y = 0;
	data->o_x = 500;
	data->o_y = 500;
	data->nb_x = 80;
	data->nb_y = 80;
	data->map = NULL;
	data->start_j = 0;
	data->flag = 0;
	data->radius = 7;
	data->start_x = data->o_x - data->radius;
	data->end_x = data->o_x + data->radius;
	data->start_y = data->o_y - data->radius;
	data->end_y = data->o_y + data->radius;
	data->nb_rays = 320;
}

void	collect_map(t_data *data)
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

void	creat_map_line(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	data->y = 0;
	while (data->map[data->x][data->y])
	{
		if (data->map[data->x][data->y] == '1')
			data->flag = 1;
		while (i < data->nb_x)
		{
			j = data->start_j + 1;
			while (j < data->nb_y)
			{
				if (data->flag == 1)
					mlx_pixel_put(data->mlx, data->win, i, j, 0xFFFFFFF);
				j++;
			}
			i++;
		}
		data->flag = 0;
		data->y++;
		i++;
		data->nb_x += 80;
	}
}

void	put_player(t_data *data)
{
	data->x = data->start_x;
	while (data->x <= data->end_x)
	{
		data->y = data->start_y;
		while (data->y <= data->end_y)
		{
			if (((data->x - data->o_x) * (data->x - data->o_x))
				+ ((data->y - data->o_y) * (data->y - data->o_y))
				<= (data->radius * data->radius))
					mlx_pixel_put(data->mlx, data->win, data->x, data->y, 0xFF0000);
			data->y++;
			printf("intern\n");
		}
			printf("extern\n");
		data->x++;
	}
}

void	push_rays(t_data *data, double rad)
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
		mlx_pixel_put(data->mlx, data->win, ox, oy, 0xFF0000);
		i++;
	}
}

void	fov_player(t_data *data)
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

int	creat_map(t_data *data)
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
	fov_player(data);
	return (0);
}

int	move_player(int key, t_data *data)
{
	if (key == 53)
		exit(1);
	if (key == 13)
	{
		data->o_x += 10;
		printf("data->o_x = %d\n", data->o_x);
		data->o_y += 10;
		printf("data->o_y = %d\n", data->o_y);
		mlx_clear_window(data->mlx, data->win);
		return(0);
	}

	return (0);
}

int	main(int ac, char **av)
{
	t_data	*data;
	char	*line;
	char	*join_lines;
	int		fd;

	(void)ac;
	(void)av;
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	init_data(data, ac, av);
	collect_map(data);
	data->mlx = mlx_init();
	if (!data->mlx)
		return (1);
	data->win = mlx_new_window(data->mlx, 1000, 1000, "game_3D");
	if (!data->win)
	{
		free(data->mlx);
		return (1);
	}
	mlx_loop_hook (data->mlx, &creat_map, data);
	mlx_hook (data->win, 2, 0, &move_player, data);
	mlx_loop(data->mlx);

}