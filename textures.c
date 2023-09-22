/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stemsama <stemsama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 01:15:07 by stemsama          #+#    #+#             */
/*   Updated: 2023/09/22 22:53:31 by stemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	to_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

t_img	*ft_texture2(t_ply	*data, char	*path, t_img *image)
{
	image->img = mlx_xpm_file_to_image(data->mlx,
			path, &image->width, &image->height);
	if (!image->img || image->width != NUM_PIXELS || image->width != NUM_PIXELS)
		affiche_er(2);
	image->addr = mlx_get_data_addr(image->img,
			&image->bits_per_pixel, &image->line_length, &image->endian);
	image->tab_color = malloc(sizeof(unsigned int *)
			* (image->width) * (image->height));
	if (!image->tab_color)
		affiche_er(2);
	return (image);
}

t_img	*ft_texture(t_ply	*data, char	*path)
{
	t_img			*image;
	int				i_bytes_per_pixel[2];
	unsigned char	rgb[3];

	image = malloc(sizeof(t_img));
	if (!image)
	{
		free(data->mydata);
		free(data);
		affiche_er(2);
	}
	image = ft_texture2(data, path, image);
	i_bytes_per_pixel[0] = 0;
	i_bytes_per_pixel[1] = image->bits_per_pixel / 8;
	while (i_bytes_per_pixel[0] < (NUM_PIXELS * NUM_PIXELS))
	{
		rgb[0] = image->addr[i_bytes_per_pixel[0] * i_bytes_per_pixel[1] + 2];
		rgb[1] = image->addr[i_bytes_per_pixel[0] * i_bytes_per_pixel[1] + 1];
		rgb[2] = image->addr[i_bytes_per_pixel[0] * i_bytes_per_pixel[1]];
		image->tab_color[i_bytes_per_pixel[0]] = to_rgb(rgb[0], rgb[1], rgb[2]);
		i_bytes_per_pixel[0]++;
	}
	return (image);
}
