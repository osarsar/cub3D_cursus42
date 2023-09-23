/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 02:13:42 by stemsama          #+#    #+#             */
/*   Updated: 2023/09/23 20:07:07 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_isdigit(int c )
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	main_2(t_ply *data)
{
	data->win = mlx_new_window(data->mlx, data->width_of_win,
			data->height_of_win, "3D_game");
	data->mydata->img = mlx_new_image(data->mlx,
			data->width_of_win, data->height_of_win);
	data->mydata->addr = mlx_get_data_addr(data->mydata->img, 
			&data->mydata->bits_per_pixel, 
			&data->mydata->line_length, &data->mydata->endian);
	mlx_hook(data->win, 2, 0, &move_player, data);
	mlx_hook(data->win, 17, 0, &close_win, data);
	mlx_loop_hook(data->mlx, &creat_map, data);
}

void	pars_2(t_ply *data)
{
	data->no_path = NULL;
	data->so_path = NULL;
	data->we_path = NULL;
	data->ea_path = NULL;
	data->f_1 = 0;
	data->f_2 = 0;
	data->f_3 = 0;
	data->c_1 = 0;
	data->c_2 = 0;
	data->c_3 = 0;
}

void	pars(t_ply	*data, int ac, char **av)
{
	int	fd;
	int	size;

	if (ac != 2)
		affiche_er(2);
	init_data(data, ac, av);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		affiche_er(2);
	size = ft_strlen(av[1]);
	if (av[1][size - 4] != '.' || av[1][size - 3] != 'c'
		|| av[1][size - 2] != 'u' || av[1][size - 1] != 'b')
	{
		printf("%c\n", av[1][size - 1]);
		write(1, "L\n", 2);
		affiche_er(2);
	}
	pars_2(data);
	get_map(fd, data);
	check_map_close(data->map);
	close(fd);
	data->height_of_win = 720;
	data->width_of_win = 1080;
}
