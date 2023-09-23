/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stemsama <stemsama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 07:45:07 by stemsama          #+#    #+#             */
/*   Updated: 2023/09/23 13:07:10 by stemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	read_config_1(char *line, t_ply *data)
{
	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
		read_config_path(line, data);
	else if (!ft_strncmp(line, "C ", 2) || !ft_strncmp(line, "F ", 2))
		read_config_f_c(line, data);
	else
	{
		free(line);
		affiche_er(2);
	}
}

char	*read_config(int fd, t_ply *data)
{
	char	*line;
	int		check;

	line = get_next_line(fd);
	if (line == NULL)
	{
		free(line);
		affiche_er(1);
	}
	check = 0;
	while ((check != 6) && line != NULL)
	{
		line = ft_strtrim_free(line, " \t");
		if (line && !ft_strcmp(line, "\n"))
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		read_config_1(line, data);
		free(line);
		line = get_next_line(fd);
		check++;
	}
	return (line);
}

void	read_config_path(char *line, t_ply *data)
{
	if (!ft_strncmp(line, "NO ", 2))
	{
		data->no_path = ft_strtrim(line, " \t\n");
		data->no_path = read_config_path_2(data->no_path);
	}
	else if (!ft_strncmp(line, "SO ", 2))
	{
		data->so_path = ft_strtrim(line, " \t\n");
		data->so_path = read_config_path_2(data->so_path);
	}
	else if (!ft_strncmp(line, "WE ", 2))
	{
		data->we_path = ft_strtrim(line, " \t\n");
		data->we_path = read_config_path_2(data->we_path);
	}
	else if (!ft_strncmp(line, "EA ", 2))
	{
		data->ea_path = ft_strtrim(line, " \t\n");
		data->ea_path = read_config_path_2(data->ea_path);
	}
}

void	get_map_2(int fd, char	*line, t_ply *data)
{
	char	*tmp_line;

	tmp_line = NULL;
	while (line != NULL)
	{
		if (!ft_strchr(line, '1'))
			affiche_er(1);
		tmp_line = ft_strjoin(tmp_line, line);
		free(line);
		line = get_next_line(fd);
	}
	tmp_line = replace_char(tmp_line, ' ', '=');
	check_char_in_map(tmp_line);
	data->map = ft_split(tmp_line, '\n');
	data->map = map_to_rectangle(data->map);
	free(tmp_line);
}
