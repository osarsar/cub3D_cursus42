/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 20:44:17 by osarsar           #+#    #+#             */
/*   Updated: 2023/09/17 08:00:28 by osarsar          ###   ########.fr       */
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

# define NUM_PIXELS 80
# define UP 13
# define DOWN 1
# define RIGHT 2
# define LEFT 0
typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_ply
{
	int		height_f_wall;
	int		width_f_wall;
	char	**map;
	char	**av;
	int		ac;
	void	*mlx;
	void	*win;
	int		x;
	int		y;
	int		p_x;
	int		p_y;
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
	double	rad;
	double	fov;
	double	face_angle;
	double	len_ray;
	double	face_rad;
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
	double	first_hx;
	double	first_hy;
	double	first_vx;
	double	first_vy;
	double	h_dx;
	double	h_dy;
	double	v_dx;
	double	v_dy;
	double	xstep;
	double	ystep;
	double	hx_wall;
	double	hy_wall;
	double	vx_wall;
	double	vy_wall;
	double	h_distance;
	double	v_distance;
	t_data	*mydata;
}t_ply;

//-----------------------------------------------------> osarsar
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
char		**ft_split(char const *s, char c);
void		*free_f(char **str, int i);
char		*fill_str(char *lil_str, const char *s, char c);
int			word_size(const char *s, char c);
int			words_numb(const char *s, char c);
void		init_data(t_ply *data, int ac, char **av);
void		put_image(t_ply *data);
int			put_image_to_letter(t_ply *data);
int			creat_map(t_ply *data);
void		put_player(t_ply *data);
void		fov_player(t_ply *data);
double		deg_to_rad(double deg);
void		first_hori_verti(t_ply *data);
char		*check_view(t_ply *data);
void		modify_depend_view(t_ply *data, char *view);
void		hori_wall_cord(t_ply *data, char *view);
void		verti_wall_cord(t_ply *data, char *view);
void		take_distance(t_ply *data);
void		push_rays(t_ply *data);
int			move_player(int key, t_ply *data);
char		*check_view_player(t_ply *data);
void		draw_view(t_ply *data);

//-----------------------------------------------------> stemsama
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