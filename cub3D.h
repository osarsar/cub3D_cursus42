/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 20:44:17 by osarsar           #+#    #+#             */
/*   Updated: 2023/09/03 00:53:21 by osarsar          ###   ########.fr       */
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
//#include <math.h>

typedef struct s_ply
{
	char	**map;
	char	**av;
	int		ac;
	void	*mlx;
	void	*win;
	void	*wall;
	void	*player;
	void	*exit;
	void	*collect;
	void	*back;
	int		x;
	int		y;

}t_ply;

char		**ft_split(char const *s, char c);
static void	*free_f(char **str, int i);
static char	*fill_str(char *lil_str, const char *s, char c);
static int	word_size(const char *s, char c);
static int	words_numb(const char *s, char c);
void		creat_map(t_ply *data);
void		init_data(t_ply *data, int ac, char **av);
#endif