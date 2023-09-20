/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stemsama <stemsama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:29:54 by stemsama          #+#    #+#             */
/*   Updated: 2023/09/20 15:33:14 by stemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	close_win(t_ply *data)
{
	mlx_destroy_window(data->mlx, data->win);
	exit(0);
	return (0);
}

// void is_pre()
// {}

// void is_rel()
// {}
