/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 20:44:17 by osarsar           #+#    #+#             */
/*   Updated: 2023/09/07 22:19:37 by osarsar          ###   ########.fr       */
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

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_ply
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
	t_data	*data;
	// t_ply	player;

}t_ply;


void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
char		**ft_split(char const *s, char c);
static void	*free_f(char **str, int i);
static char	*fill_str(char *lil_str, const char *s, char c);
static int	word_size(const char *s, char c);
static int	words_numb(const char *s, char c);
void		collect_map(t_ply *data);
void		init_data(t_ply *data, int ac, char **av);
void		put_image(t_ply *data);
int			put_image_to_letter(t_ply *data);
int	creat_map(t_ply *data);
#endif