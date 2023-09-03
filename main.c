/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 20:41:40 by osarsar           #+#    #+#             */
/*   Updated: 2023/09/03 11:08:14 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_data(t_ply *data, int ac, char **av)
{
	data->ac = ac;
	data->av = av;
	data->map = 0;
}

void	creat_map(t_ply *data)
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

int	main(int ac, char **av)
{
	t_ply	*data;
	char	*line;
	char	*join_lines;
	int		fd;

	(void)ac;
	(void)av;
	data = malloc(sizeof(t_ply));
	if (!data)
		return (1);
	init_data(data, ac, av);
	creat_map(data);
	data->mlx = mlx_init();
	if (!data->mlx)
		return (1);
	data->win = mlx_new_window(data->mlx, 1000, 1000, "game_3D");
	if (!data->win)
	{
		free(data->mlx);
		return (1);
	}
	// put_image(data);
	// put_image_to_letter(data);
	int	i = 0;
	int	j;
	int	nb_i = 80;
	int	nb_j = 80;
	int	start_j = 0;
	int	x = 0;
	int	y = 0;
	int flag = 0;

	while (data->map[x])
	{
		y = 0;
		i = 0;
		nb_i = 80;
		while (data->map[x][y])
		{
			if (data->map[x][y] == '1')
				flag = 1;
			while (i < nb_i)
			{
				j = start_j + 1;
				while (j < nb_j)
				{
					if (flag == 1)
						mlx_pixel_put(data->mlx, data->win, i, j, 0xFFFFFFF);
					j++;
				}
				i++;
			}
			flag = 0;
			y++;
			i++;
			nb_i += 80;
		}
		nb_j += 80;
		start_j += 80;
		x++;
	}
	while (j < 1000)
	{
		i = 0;
		nb_i = 80;
		while (i < 1000)
		{
			while (i < nb_i)
			{
				j = start_j + 1;
				while (j < nb_j)
				{
					if (data->map[x][y] == 1)
						mlx_pixel_put(data->mlx, data->win, i, j, 0xFFFFFFF);
					j++;
				}
				i++;
			}
			x++;
			y++;
			i++;
			nb_i += 80;
			while (i < nb_i)
			{
				j = start_j + 1; 
				while (j < nb_j)
				{
					if (data->map[x][y] == 1)
						mlx_pixel_put(data->mlx, data->win, i, j, 0xFFFFFFF);
					j++;
				}
				i++;
			}
			x++;
			y++;
		}
		nb_j += 80;
		start_j += 80;
	}
	x = 1000 / 2;
    y = 1000 / 2;
    int radius = 7;
	int start_x = x - radius;
	int	end_x = x + radius;
	int start_y = y - radius;
	int	end_y = y + radius;

	printf("x = %d\ty = %d\n", start_x - x, start_y - y);
	while (start_x <= end_x)
	{
		start_y = y - radius;
		while (start_y <= end_y)
		{
			if (((start_x - x) * (start_x - x)) + ((start_y - y) * (start_y - y)) <= (radius * radius))
			mlx_pixel_put(data->mlx, data->win, start_x, start_y, 0xFF0000);
			start_y++;
		}
		start_x++;
	}
	while (y > 450)
	{
		mlx_pixel_put(data->mlx, data->win, x, y, 0xFF0000);
			y--;
	}
	mlx_loop_hook (data->mlx, &mlx_pixel_put, data);
	mlx_loop(data->mlx);
}
