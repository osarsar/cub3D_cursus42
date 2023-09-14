/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stemsama <stemsama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 05:32:46 by stemsama          #+#    #+#             */
/*   Updated: 2023/09/14 08:17:11 by stemsama         ###   ########.fr       */
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
		affiche_er(2);
	else if (j != 0 && map[i][j - 1] == '0')
		affiche_er(1);
	else if (map[i][j + 1] == '0')
		affiche_er(1);
}

void	like_bfs_algo(char **map)
{
	int	i;
	int	j;

	i = -1;
	printf("\nmap rectangle:\n");
	while (map[++i])
		printf("%s\n", map[i]);
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
	path += 2;
	path = ft_strtrim(path, " \t\n");
	if (ft_strchr(path, ' ') || ft_strchr(path, '\t'))
		affiche_er(1);
	return (path);
}
