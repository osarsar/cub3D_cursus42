/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stemsama <stemsama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 20:44:17 by osarsar           #+#    #+#             */
/*   Updated: 2023/09/14 09:10:53 by stemsama         ###   ########.fr       */
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

typedef struct s_data {
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
	int		speed;
	int		len_ray;
	double	angle;
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	int		f_1;
	int		f_2;
	int		f_3;
	int		c_1;
	int		c_2;
	int		c_3;
	t_data	*data;
}t_ply;

void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
char		**ft_split(char const *s, char c);
void		*free_f(char **str, int i);
char		*fill_str(char *lil_str, const char *s, char c);
int			word_size(const char *s, char c);
int			words_numb(const char *s, char c);
void		collect_map(t_ply *data);
void		init_data(t_ply *data, int ac, char **av);
void		put_image(t_ply *data);
int			put_image_to_letter(t_ply *data);
int			creat_map(t_ply *data);
void		put_player(t_ply *data);
void		fov_player(t_ply *data);
double		deg_to_rad(double deg);

//-----------------------------------------------------> tols1.c
void		pars(t_ply	*data, int ac, char **av);
void		get_map(int fd, t_ply *data);
void		read_config_f_c(char *line, t_ply *data);
void		check_number(char **list_color, int check, t_ply *data);
void		check_comma(char *line);

//-----------------------------------------------------> tols2.c
void		ft_lstclear_double(char **lstmap);
void		check_line1(char *line1);
void		check_line_fin(char *line1);
void		check_char_in_map(char *str);
void		check_line_extrem(char *linee);

//-----------------------------------------------------> tols3.c
void		affiche_er(int a);
char		*replace_char(char *tmp_line, char old, char new);
int			max_size_col(char **map);
char		**map_to_rectangle(char **map);
char		*rest_to_rect(int max_size, int size);

//-----------------------------------------------------> tols4.c
int			size_map_line(char **map);
void		go_to_check(char **map, int i, int j);
void		like_bfs_algo(char **map);
void		check_map_close(char **map);
char		*read_config_path_2(char *path);

//-----------------------------------------------------> tols5.c
void		read_config_1(char *line, t_ply *data);
char		*read_config(int fd, t_ply *data);
void		read_config_path(char *line, t_ply *data);

//-----------------------------------------------------> libft1.c
char		*ft_strtrim(char *s1, char *set);

//-----------------------------------------------------> libft2.c
int			ft_strncmp(const char *s1, const char *s2, size_t len);
int			ft_strcmp(char *s1, char *s2);
int			ft_atoi(char *str);
int			ft_atoi_trois(void);
#endif