/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 01:15:07 by stemsama          #+#    #+#             */
/*   Updated: 2023/09/18 20:08:35 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int to_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void ft_texture(t_ply	*data)
{
	t_img			image;
	int				width;
	int				height;
	int				i;
	unsigned char	rgb[3];

	image.img = mlx_xpm_file_to_image(data->mlx, "./images/wall.xpm", &width, &height);
	if (!image.img || width != NUM_PIXELS || height != NUM_PIXELS)
		affiche_er(2);
	image.addr = mlx_get_data_addr(image.img,
	&image.bits_per_pixel, &image.line_length, &image.endian);
	data->tab_color = malloc(sizeof(unsigned int *) * (width) * (height));
	if (!data->tab_color)
		affiche_er(2);
	i = 0;
    int bytes_per_pixel = image.bits_per_pixel / 9;
	while (i < (NUM_PIXELS * NUM_PIXELS))
	{
		rgb[0] = image.addr[i * bytes_per_pixel + 2];
        rgb[1] = image.addr[i * bytes_per_pixel + 1];
        rgb[2] = image.addr[i * bytes_per_pixel];
        data->tab_color[i] = to_rgb(rgb[0], rgb[1], rgb[2]);
		// printf("i = %d; data->tab_color[i] = %d\n", i, data->tab_color[i]);
		i++;
	}
}
