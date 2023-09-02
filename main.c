/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 20:41:40 by osarsar           #+#    #+#             */
/*   Updated: 2023/09/03 00:52:22 by osarsar          ###   ########.fr       */
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
	put_image(data);
	put_image_to_letter(data);
	mlx_loop_hook (data->mlx, &put_image_to_letter, data);
	mlx_loop(data->mlx);
}
