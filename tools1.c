/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stemsama <stemsama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 05:09:13 by stemsama          #+#    #+#             */
/*   Updated: 2023/09/11 06:31:29 by stemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_lstclear_double(char **lstmap)
{
	int	i;

	i = 0;
	while (lstmap[i])
		free(lstmap[i++]);
	free(lstmap);
}

void	check_line_extrem(char *linee)
{
	int	size;

	size = ft_strlen(linee);
	if (linee[size - 1] != '\n')
		check_line_fin(linee);
	if (linee[0] != '1' || linee[size - 2] != '1')
		affiche_er(1);
}

void	check_line1(char *line1)
{
	int	i;
	int	size;

	i = 0;
	size = ft_strlen(line1);
	while (i < size - 1)
	{
		if (line1[i] == '1')
			i++;
		else
		{
			affiche_er(1);
			free(line1);
		}
	}
}

void	check_line_fin(char *line1)
{
	int	i;
	int	size;

	i = 0;
	size = ft_strlen(line1);
	while (i < size)
	{
		if (line1[i] == '1')
			i++;
		else
			affiche_er(1);
	}
}
void	check_char_in_map(char *str)
{
	int	i;
	int	p;

	i = 0;
	p = 0;
	while (str[i])
	{
		if (str[i] == 'N' || str[i] == 'W'
			|| str[i] == 'E' || str[i] == 'S')
			p++;
		if (str[i] != '1' && str[i] != '0' \
			&& str[i] != '\n' && str[i] != '\0' && str[i] != 'N' \
			 && str[i] != 'E' && str[i] != 'W' && str[i] != 'S')
			affiche_er(1);
		i++;
	}
	if (p != 1)
		affiche_er(1);
}

void	get_map(int fd, t_ply *data)
{
	char	*line;
	char	*tmp_line;

	tmp_line = NULL;
	line = get_next_line(fd);
	// line = ft_strtrim(line, " ");
	if (line == NULL)
	{
		free(line);
		affiche_er(1);
	}
	check_line1(line);
	while (line != NULL)
	{
		check_line_extrem(line);
		tmp_line = ft_strjoin(tmp_line, line);
		free(line);
		line = get_next_line(fd);
	}
	check_char_in_map(tmp_line);
	data->map = ft_split(tmp_line, '\n');
}

void	affiche_er(int a)
{
	if (a == 1)
		write(2, "map non valide\n", 15);
	else if (a == 2)
		write(2, "Error\n", 6);
	exit(1);
}

void pars(t_ply	*data, int ac, char **av)
{
	int	fd;
	
	if (ac != 2)
		affiche_er(2);
	init_data(data, ac, av);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		affiche_er(2);
	get_map(fd, data);
}
