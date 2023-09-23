/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stemsama <stemsama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 05:32:46 by stemsama          #+#    #+#             */
/*   Updated: 2023/09/23 12:59:05 by stemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	size_map_line(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		i++;
	}
	return (i);
}

void	go_to_check(char **map, int i, int j)
{
	if (i != 0 && map[i - 1][j] == '0')
		affiche_er(1);
	else if (i != (size_map_line(map) - 1) && map[i + 1][j] == '0')
		affiche_er(1);
	else if (j != 0 && map[i][j - 1] == '0')
		affiche_er(1);
	else if (map[i][j + 1] == '0')
		affiche_er(1);
}

void	like_bfs_algo(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '=')
				go_to_check(map, i, j);
			j++;
		}
		i++;
	}
}

void	check_map_close(char **map)
{
	int	i;

	i = 0;
	check_line1(map[0]);
	while (map[i])
	{
		check_line_extrem(map[i]);
		i++;
	}
	check_line_fin(map[i - 1]);
	like_bfs_algo(map);
}

char	*read_config_path_2(char *path)
{
	char	*return_value;

	return_value = ft_strdup(path + 2);
	free(path);
	return_value = ft_strtrim_free(return_value, " \t\n");
	if (!ft_strcmp(return_value, ""))
	{
		free(return_value);
		affiche_er(1);
	}
	return (return_value);
}
