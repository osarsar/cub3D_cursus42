/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   speed.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 16:01:04 by osarsar           #+#    #+#             */
/*   Updated: 2023/09/28 16:03:39 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	set(int keycode, t_ply *data)
{
	if (keycode == UP)
		data->k_up = 1;
	else if (keycode == DOWN)
		data->k_down = 1;
	else if (keycode == LEFT)
		data->k_left = 1;
	else if (keycode == RIGHT)
		data->k_right = 1;
	else if (keycode == 123)
		data->tr_left = 1;
	else if (keycode == 124)
		data->tr_right = 1;
	else if (keycode == 53)
		exit(0);
	return (0);
}

int	reset(int keycode, t_ply *data)
{
	if (keycode == UP)
		data->k_up = 0;
	else if (keycode == DOWN)
		data->k_down = 0;
	else if (keycode == LEFT)
		data->k_left = 0;
	else if (keycode == RIGHT)
		data->k_right = 0;
	else if (keycode == 123)
		data->tr_left = 0;
	else if (keycode == 124)
		data->tr_right = 0;
	return (0);
}
