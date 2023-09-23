/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stemsama <stemsama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 05:09:13 by stemsama          #+#    #+#             */
/*   Updated: 2023/09/23 13:07:08 by stemsama         ###   ########.fr       */
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

void	check_number_2(char **list_color, int i)
{
	int	j;

	j = 0;
	while (list_color[i][j])
	{
		if (!ft_isdigit(list_color[i][j]))
			affiche_er(2);
		j++;
	}
	if (ft_strchr(list_color[i], ' ') || ft_strchr(list_color[i], '\t'))
		affiche_er(2);
	if (ft_atoi(list_color[i]) > 255 || ft_atoi(list_color[i]) < 0)
		affiche_er(1);
}

void	check_number(char **list_color, int check, t_ply *data)
{
	int	i;

	i = 0;
	while (list_color[i])
	{
		list_color[i] = ft_strtrim_free(list_color[i], " \t");
		check_number_2(list_color, i);
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
	free_color(list_color, i);
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
	free(line);
	line = NULL;
}

//line = read_config(fd, data); ->| now line = first line of map
void	get_map(int fd, t_ply *data)
{
	char	*line;

	line = read_config(fd, data);
	if (!data->no_path || !data->so_path || !data->we_path || !data->ea_path)
		affiche_er(1);
	line = ft_strtrim_free(line, " \t");
	while (!ft_strcmp(line, "\n"))
	{
		free(line);
		line = get_next_line(fd);
		if (!ft_strchr(line, '1'))
			line = ft_strtrim_free(line, " \t");
	}
	get_map_2(fd, line, data);
}
