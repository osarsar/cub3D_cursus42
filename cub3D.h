/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 20:44:17 by osarsar           #+#    #+#             */
/*   Updated: 2023/09/04 10:18:29 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "get_next_line.h"
# include <mlx.h>
# include <math.h>

// typedef struct s_ply
// {
// 	int x;
	
// }t_ply;

typedef struct s_data
{
	char	**map;
	char	**av;
	int		ac;
	void	*mlx;
	void	*win;
	int		x;
	int		y;
	int		o_x;
	int		o_y;
	int		start_x;
	int		start_y;
	int		start_j;
	int		end_x;
	int		end_y;
	int		nb_x;
	int		nb_y;
	int		flag;
	int		radius;
	int		nb_rays;
	// t_ply	player;

}t_data;

char		**ft_split(char const *s, char c);
static void	*free_f(char **str, int i);
static char	*fill_str(char *lil_str, const char *s, char c);
static int	word_size(const char *s, char c);
static int	words_numb(const char *s, char c);
void		collect_map(t_data *data);
void		init_data(t_data *data, int ac, char **av);
void		put_image(t_data *data);
int			put_image_to_letter(t_data *data);
int	creat_map(t_data *data);
#endif