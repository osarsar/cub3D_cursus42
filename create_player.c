/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 08:15:37 by osarsar           #+#    #+#             */
/*   Updated: 2023/09/14 05:28:46 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	put_player(t_ply *data)
{
	data->start_x = data->p_x - data->radius;
	data->end_x = data->p_x + data->radius;
	data->start_y = data->p_y - data->radius;
	data->end_y = data->p_y + data->radius;
	data->x = data->start_x;
	while (data->x <= data->end_x)
	{
		data->y = data->start_y;
		while (data->y <= data->end_y)
		{
			if (((data->x - data->p_x) * (data->x - data->p_x))
				+ ((data->y - data->p_y) * (data->y - data->p_y))
				<= (data->radius * data->radius))
				my_mlx_pixel_put(data->mydata, data->x, data->y, 0x00FF0000);
			data->y++;
		}
		data->x++;
	}
}

void	push_rays(t_ply *data, double rad)
{
	// int	ox;
	// int	oy;
	int	i;
	(void)rad;
	// int len =

		i = 0;
		while (i <= 3)
		{
		// while (data->xstep < 1040 && data->ystep < 1040)
		// {
			// printf("---->here\n");
			// ox = data->p_x - (i * cos(rad));
			// oy = data->p_y - (i * sin(rad));
			// if (data->map[(int)(data->xstep / 80)][(int)(data->ystep / 80)] == '1')
			// 	break;
			// printf("data->xstep = %f\n", data->xstep);
			// printf("data->ystep = %f\n", data->ystep);
			my_mlx_pixel_put(data->mydata, (int)data->xstep, (int)data->ystep, 0x00FF0000);
			// i++;
			data->xstep += data->h_dx;
			data->ystep += data->h_dy;
			i++;
		}
}
void	first_hori_verti(t_ply *data, double rad)
{
	data->first_hy = (data->p_y / 80) * 80;
	data->first_hx = (data->first_hy - data->p_y / tan(rad));//data->p_x +
	data->first_vx = (data->p_x / 80) * 80;
	data->first_vy = data->p_y + ((data->first_vx - data->p_x) * tan(rad));
}

void	padding(t_ply *data, double rad)
{
	data->h_dy = 80;
	data->h_dx = data->h_dy / tan(rad);
	data->v_dx = 80;
	data->v_dy = data->v_dx * tan(rad);
}
char *check_view(double rad)
{
	if ((rad >= 0 && rad <= M_PI))
	{
		if (rad >= 0 && rad <= (0.5 * M_PI))
			return ("up_left");
		else
			return ("up_right");
	}
	else
	{
		if ((rad >= M_PI && rad <= (M_PI + (0.5 * M_PI))))
			return ("down_left");
		else
			return ("down_right");
	}
}

void init_angle(double *rad)
{
	*rad = fmod(*rad, (2 * M_PI));
	if (*rad < 0)
		*rad = (2 * M_PI) + *rad;
}

void	fov_player(t_ply *data)
{
	double	rad;
	char	*view = NULL;

	rad = deg_to_rad(data->angle);
	init_angle(&rad);
	first_hori_verti(data, rad);
	padding(data, rad);
	view = check_view(rad);

	if (!ft_strcmp(view, "up_left"))
	{
		data->first_hy = (data->p_y / 80) * 80;
		data->first_hx = data->p_x - ((data->p_y - data->first_hy) / tan(rad));
		data->h_dx = (data->h_dy / tan(rad)) * -1;
		data->h_dy = -80;
	}
	else if (!ft_strcmp(view, "up_right"))
	{
		data->first_hy = (data->p_y / 80) * 80;
		data->first_hx = data->p_x - ((data->p_y - data->first_hy) / tan(rad));
		data->h_dx = (data->h_dy / tan(rad)) * -1;
		data->h_dy = -80;
	}
	else if (!ft_strcmp(view, "down_left"))
	{
		data->first_hy = ((data->p_y / 80) * 80) + 80;
		data->first_hx = data->p_x - ((data->p_y - data->first_hy) / tan(rad));
		data->h_dx = (data->h_dy / tan(rad));
		data->h_dy = 80;
	}
	else if (!ft_strcmp(view, "down_right"))
	{
		data->first_hy = ((data->p_y / 80) * 80) + 80;
		data->first_hx = data->p_x - ((data->p_y - data->first_hy) / tan(rad));
		data->h_dx = (data->h_dy / tan(rad));
		data->h_dy = 80;
	}
	data->xstep = data->first_hx;
	data->ystep = data->first_hy;
	// printf("data->map = %c\n", data->map[(int)data->xstep / 80][(int)data->ystep / 80]);
	while (1)
	{
		my_mlx_pixel_put(data->mydata, (int)data->xstep, (int)data->ystep, 0x00FF0000);
		if (data->map[(int)data->xstep / 80][(int)data->ystep / 80] == '1')
			break;
		data->xstep += data->h_dx;
		data->ystep += data->h_dy;
	}
	//push_rays(data, rad);
	// if (!ft_strcmp(view, "up_right") || !ft_strcmp(view, "up_left"))
	// 	data->ystep--;
	
	// // colomn = 0;
	// while (colomn < data->nb_rays)
	// {
	// 	colomn++;
	// 	rad += 0.001;
	// }
}
