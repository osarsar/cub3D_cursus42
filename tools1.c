/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stemsama <stemsama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 05:09:13 by stemsama          #+#    #+#             */
/*   Updated: 2023/09/16 18:24:42 by stemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_comma(char *line)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (line[i])
	{
		if (line[i] == ',')
			check++;
		i++;
	}
	if (check != 2)
		affiche_er(1);
}

void	check_number(char **list_color, int check, t_ply *data)
{
	int	i;

	i = 0;
	while (list_color[i])
	{
		list_color[i] = ft_strtrim(list_color[i], " \t");
		if (ft_strchr(list_color[i], ' ') || ft_strchr(list_color[i], '\t'))
			affiche_er(2);
		if (ft_atoi(list_color[i]) > 255 || ft_atoi(list_color[i]) < 0)
			affiche_er(1);
		i++;
	}
	if (check == 1)
	{
		data->f_1 = ft_atoi(list_color[0]);
		data->f_2 = ft_atoi(list_color[1]);
		data->f_3 = ft_atoi(list_color[2]);
	}
	else if (check == 2)
	{
		data->c_1 = ft_atoi(list_color[0]);
		data->c_2 = ft_atoi(list_color[1]);
		data->c_3 = ft_atoi(list_color[2]);
	}
}

void	read_config_f_c(char *line, t_ply *data)
{
	char	**list_color;
	int		check;

	check = -1;
	if (!ft_strncmp(line, "F", 1))
		check = 1;
	else if (!ft_strncmp(line, "C", 1))
		check = 2;
	line += 1;
	line = ft_strtrim(line, " \t\n");
	check_comma(line);
	list_color = ft_split(line, ',');
	if (!list_color[0] || !list_color[1] || !list_color[2])
		affiche_er(1);
	check_number(list_color, check, data);
	printf("2 config c_f :%s\n", line);
}

//line = read_config(fd, data); ->| now line = first line of map
void	get_map(int fd, t_ply *data)
{
	char	*line;
	char	*tmp_line;

	tmp_line = NULL;
	line = read_config(fd, data);
	if (!data->no_path || !data->so_path || !data->we_path || !data->ea_path)
		affiche_er(1);
	line = ft_strtrim(line, " \t");
	while (!ft_strcmp(line, "\n"))
	{
		line = get_next_line(fd);
		line = ft_strtrim(line, " \t");
	}
	while (line != NULL)
	{
		tmp_line = ft_strjoin(tmp_line, line);
		free(line);
		line = get_next_line(fd);
	}
	tmp_line = replace_char(tmp_line, ' ', '=');
	check_char_in_map(tmp_line);
	data->map = ft_split(tmp_line, '\n');
	data->map = map_to_rectangle(data->map);
	check_map_close(data->map);
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
	data->height_f_wall = size_map_line(data->map) * NUM_PIXELS;
	data->width_f_wall = max_size_col(data->map) * NUM_PIXELS;
}
