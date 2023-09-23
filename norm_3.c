/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stemsama <stemsama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 02:13:42 by stemsama          #+#    #+#             */
/*   Updated: 2023/09/23 02:17:56 by stemsama         ###   ########.fr       */
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

void	pars(t_ply	*data, int ac, char **av)
{
	int	fd;

	if (ac != 2)
		affiche_er(2);
	init_data(data, ac, av);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		affiche_er(2);
	if (ft_strcmp(ft_strchr(av[1], '.'), ".cub"))
		affiche_er(2);
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
	get_map(fd, data);
	check_map_close(data->map);
	close(fd);
	data->height_of_win = 720;
	data->width_of_win = 1080;
}
