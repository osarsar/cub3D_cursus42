/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stemsama <stemsama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 20:44:17 by osarsar           #+#    #+#             */
/*   Updated: 2023/09/29 18:51:39 by stemsama         ###   ########.fr       */
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

# define NUM_PIXELS 64
# define UP 13
# define DOWN 1
# define RIGHT 2
# define LEFT 0

typedef struct s_img {
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				width;
	int				height;
	int				endian;
	unsigned int	*tab_color;
}				t_img;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_ply
{
	int				height_of_win;
	int				width_of_win;
	char			**map;
	char			**av;
	int				ac;
	void			*mlx;
	void			*win;
	int				x;
	int				y;
	double			p_x;
	double			p_y;
	int				start_x;
	int				start_y;
	int				start_j;
	int				end_x;
	int				end_y;
	int				nb_x;
	int				nb_y;
	int				flag;
	int				radius;
	int				nb_rays;
	int				speed;
	double			rad;
	double			fov;
	double			face_angle;
	double			len_ray;
	double			face_rad;
	double			angle;
	char			*no_path;
	char			*so_path;
	char			*we_path;
	char			*ea_path;
	int				f_1;
	int				f_2;
	int				f_3;
	int				c_1;
	int				c_2;
	int				c_3;
	int				f;
	int				c;
	double			first_hx;
	double			first_hy;
	double			first_vx;
	double			first_vy;
	double			h_dx;
	double			h_dy;
	double			v_dx;
	double			v_dy;
	double			xstep;
	double			ystep;
	double			hx_wall;
	double			hy_wall;
	double			vx_wall;
	double			vy_wall;
	double			h_distance;
	double			v_distance;
	double			x_wall;
	double			y_wall;
	int				check_h_v;
	int				k_up;
	int				k_down;
	int				k_left;
	int				k_right;
	int				tr_right;
	int				tr_left;
	t_data			*mydata;
	t_img			*img;
	t_img			*img_n;
	t_img			*img_s;
	t_img			*img_w;
	t_img			*img_e;
	t_img			*img_4[4];
}t_ply;

/*-----------------------------------------------------> create_map.c*/
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
void		put_pixel_to_image(t_ply *data, int i, int j);
void		creat_map_line(t_ply *data);
int			creat_map(t_ply *data, int key);

/*-----------------------------------------------------> create_player.c*/
void		first_hori_verti(t_ply *data);
void		padding(t_ply *data);
int			get_ofset_colomn(t_ply *data);
void		fov_player(t_ply *data);

/*-----------------------------------------------------> create_map.c*/
void		raycast_up_left(t_ply *data);
void		raycast_up_right(t_ply *data);
void		raycast_down_left(t_ply *data);
void		raycast_down_right(t_ply *data);
void		modify_depend_view(t_ply *data, char *view);

/*-----------------------------------------------------> player_view.c*/
char		*check_view_player(t_ply *data);
char		*check_view(t_ply *data);
void		verti_wall_cord(t_ply *data, char *view);
void		hori_wall_cord(t_ply *data, char *view);
void		take_distance(t_ply *data);

/*-----------------------------------------------------> main.c*/
void		init_data(t_ply *data, int ac, char **av);
double		deg_to_rad(double deg);
void		push_rays(t_ply *data);
int			move_player(int key, t_ply *data);

/*-----------------------------------------------------> view.c*/
void		init_angle(t_ply *data);
void		init_angle_2pi(t_ply *data);
void		draw_view(t_ply *data);
void		view_to_start(t_ply *data);
double		init_rad(t_ply *data, double rad);

/*-----------------------------------------------------> tols1.c*/
void		check_number_2(char **list_color, int i);
void		get_map(int fd, t_ply *data);
void		read_config_f_c(char *line, t_ply *data);
void		check_number(char **list_color, int check, t_ply *data);
void		check_comma(char *line);

/*-----------------------------------------------------> tols2.c*/
void		ft_lstclear_double(char **lstmap);
void		check_line1(char *line1);
void		check_line_fin(char *line1);
void		check_char_in_map(char *str);
void		check_line_extrem(char *linee);

/*-----------------------------------------------------> tols3.c*/
void		affiche_er(int a);
char		*replace_char(char *tmp_line, char old, char new);
int			max_size_col(char **map);
char		**map_to_rectangle(char **map);
char		*rest_to_rect(int max_size, int size);

/*-----------------------------------------------------> tols4.c*/
int			size_map_line(char **map);
void		go_to_check(char **map, int i, int j);
void		like_bfs_algo(char **map);
void		check_map_close(char **map);
char		*read_config_path_2(char *path);

/*-----------------------------------------------------> speed.c*/
int			set(int keycode, t_ply *data);
int			reset(int keycode, t_ply *data);
/*-----------------------------------------------------> tols5.c*/
void		read_config_1(char *line, t_ply *data);
char		*read_config(int fd, t_ply *data);
void		read_config_path(char *line, t_ply *data);
void		get_map_2(int fd, char	*line, t_ply *data);

/*-----------------------------------------------------> libft1.c*/
char		*ft_strtrim(char *s1, char *set);
char		*ft_strtrim_free(char *s1, char *set);

/*-----------------------------------------------------> libft2.c*/
int			ft_strncmp(const char *s1, const char *s2, size_t len);
int			ft_strcmp(char *s1, char *s2);
int			ft_atoi(char *str);
int			ft_atoi_trois(void);

/*-----------------------------------------------------> libft3.c*/
char		**ft_split(char const *s, char c);
void		*free_f(char **str, int i);
char		*fill_str(char *lil_str, const char *s, char c);
int			word_size(const char *s, char c);
int			words_numb(const char *s, char c);

/*-----------------------------------------------------> textures.c*/
t_img		*ft_texture(t_ply	*data, char	*path);
int			to_rgb(int r, int g, int b);

/*-----------------------------------------------------> norm_1.c*/
void		free_color(char **list_color, int i);
void		draw_map_3d(t_ply *data, int colomn);
void		move_player_2_up(t_ply *data, char *view);
void		move_player_2_do(t_ply *data, char *view);
int			move_player_2(t_ply *data, int key);

/*-----------------------------------------------------> norm_2.c*/
int			close_win(t_ply *data);
void		move_player_2_a(t_ply *data, int key, char *view);
void		move_player_2_b(t_ply *data, int x_tmp, int y_tmp);
int			cal_str_wall(int h_win, int h_wall);
int			cal_end_wall(int h_win, int h_wall);

/*-----------------------------------------------------> norm_3.c*/
void		main_2(t_ply *data);
int			ft_isdigit(int c );
void		pars(t_ply	*data, int ac, char **av);

#endif