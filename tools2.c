/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stemsama <stemsama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 23:29:34 by stemsama          #+#    #+#             */
/*   Updated: 2023/09/14 05:44:10 by stemsama         ###   ########.fr       */
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

void	check_line1(char *line1)
{
	int	i;
	int	size;

	i = 0;
	size = ft_strlen(line1);
	while (i < size - 1)
	{
		if (line1[i] == '1' || line1[i] == '=')
			i++;
		else
		{
			free(line1);
			affiche_er(1);
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
		if (line1[i] == '1' || line1[i] == '=')
			i++;
		else
			affiche_er(1);
	}
}

void	check_line_extrem(char *linee)
{
	int	size;

	size = ft_strlen(linee);
	if ((linee[0] != '1' && linee[0] != '=')
		|| (linee[size - 1] != '1' && linee[size - 1] != '='))
		affiche_er(1);
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
		if (str[i] != '1' && str[i] != '0' && str[i] != '=' \
			&& str[i] != '\n' && str[i] != '\0' && str[i] != 'N' \
			&& str[i] != 'E' && str[i] != 'W' && str[i] != 'S')
			affiche_er(1);
		if (str[i + 1] && str[i] == '\n')
			if (str[i + 1] == '\n')
				affiche_er(1);
		i++;
	}
	if (str[i - 1] == '\n')
		affiche_er(1);
	if (p != 1)
		affiche_er(1);
}
