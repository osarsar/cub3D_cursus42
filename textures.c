/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stemsama <stemsama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 01:15:07 by stemsama          #+#    #+#             */
/*   Updated: 2023/09/17 05:36:07 by stemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int to_rgb(int r, int g, int b, int t)
{
	return (r << 24 | g << 16 | b << 8 | t);
}

void ft_texture(t_ply	*data)
{
	int				width;
	int				height;
	// unsigned int	*tab_color;
	// unsigned int	*read_color;
	// int				i;

    data->mydata->img = mlx_xpm_file_to_image(data->mlx, "./images/wall.xpm", &width, &height);
	if (!data->mydata->img || width != NUM_PIXELS || height != NUM_PIXELS)
		affiche_er(2);
	// read_color = (unsigned int *)mlx_get_data_addr(data->mydata->img,
	data->mydata->addr = mlx_get_data_addr(data->mydata->img,
	&data->mydata->bits_per_pixel, &data->mydata->line_length, &data->mydata->endian);
	// tab_color = malloc(sizeof(unsigned int) * (NUM_PIXELS) * (NUM_PIXELS));
	// if (!tab_color)
	// 	affiche_er(2);
	// i = 0;
	// while (i < (NUM_PIXELS * NUM_PIXELS))
	// {
	// 	tab_color[i] = to_rgb(read_color[i], read_color[i + 1],
	// 	read_color[i + 2], read_color[i + 3]);
	// 	i += 4;
	// }
	printf("width = %d\n", width);
	printf("read_color[0] = %d\n", data->mydata->addr[0]);
	printf("data->mydata->addr[1] = %d\n", data->mydata->addr[1]);
	printf("data->mydata->addr[2] = %d\n", data->mydata->addr[1206]);
	printf("data->mydata->addr[3] = %d\n", data->mydata->addr[13]);
	exit(0);
}
