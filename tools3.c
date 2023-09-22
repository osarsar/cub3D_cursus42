/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stemsama <stemsama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 04:03:43 by stemsama          #+#    #+#             */
/*   Updated: 2023/09/22 02:28:07 by stemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	affiche_er(int a)
{
	if (a == 1)
		write(2, "Error\n", 6);
	else if (a == 2)
		write(2, "Error\n", 6);
	exit(1);
}

char	*replace_char(char *tmp_line, char old, char new)
{
	int	i;

	i = 0;
	while (tmp_line[i])
	{
		if (tmp_line[i] == old)
			tmp_line[i] = new;
		i++;
	}
	return (tmp_line);
}

int	max_size_col(char **map)
{
	int		i;
	size_t	max_size;

	i = -1;
	max_size = 0;
	while (map[++i])
	{
		if (max_size < ft_strlen(map[i]))
			max_size = ft_strlen(map[i]);
	}
	return (max_size);
}

char	*rest_to_rect(int max_size, int size)
{
	char	*rest;
	int		i;

	i = 0;
	rest = malloc(sizeof(char) * (max_size - size + 1));
	if (!rest)
		affiche_er(2);
	while (i < max_size - size)
	{
		rest[i] = '=';
		i++;
	}
	rest[i] = '\0';
	return (rest);
}

char	**map_to_rectangle(char **map)
{
	int		i;
	int		max_size;
	char	*rest;

	i = 0;
	max_size = max_size_col(map);
	while (map[i])
	{
		rest = rest_to_rect(max_size, ft_strlen(map[i]));
		map[i] = ft_strjoin(map[i], rest);
		free(rest);
		i++;
	}
	return (map);
}
