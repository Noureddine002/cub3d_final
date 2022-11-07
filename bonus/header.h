/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 11:07:16 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/11/07 03:29:28 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include<stdio.h>
# include<stdlib.h>
# include<fcntl.h>
# include<string.h>
# include<unistd.h>
# include<mlx.h>
# include <math.h>
# include <limits.h>

# define KEY_W 13
# define KEY_S 1
# define KEY_A 0
# define KEY_D 2
# define KEY_RIGHT 124
# define KEY_LEFT 123
# define KEY_CLOSE 53
# define EVENT_CLOSE 17
# define WIN_W 1078
# define WIN_H 500

# define FOV_ANGLE 1.0471975512 //60 * (M_PI/180)
# define NUM_RAYS 360

# define TILESIZE 32

# define BUFFER_SIZE 1

# define GROUD "assets/ground.xpm"
# define WALL "assets/wall.xpm"
# define PLAYER "assets/player.xpm"

typedef struct s_colors
{
	int	floor[3];
	int	ceilling[3];
}	t_colors;

typedef struct s_ray
{
	double	rayang;
	double	pos_whor_hitx;
	double	pos_whor_hity;
	double	pos_wver_hitx;
	double	pos_wver_hity;
	double	distance_ray;
	int		up_dir;
	int		down_dir;
	int		left_dir;
	int		right_dir;
	int		column_id;
	int		horr_line;
	int		vert_line;
}	t_ray;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	radius;
	double	turndirec;
	double	walkdir;
	double	walkdirecside;
	double	rot_nang;
	double	movespeed;
	double	movestep;
	double	rotationspeed;
	void	*player;
}	t_player;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	char	*dst;
	int		newx;
	int		newy;
}	t_img;

typedef struct s_mini_map
{
	double		mn_pos_x;
	double		mn_pos_y;
}	t_mini_map;

typedef struct s_map
{
	char		**map_grid;
	char		gamer;
	int			map_width_x;
	int			map_height_y;
	void		*ground;
	void		*wall;
	int			img_w;
	int			img_h;
	void		*mlx;
	void		*win;
	void		*win2;
	int			i;
	int			j;
	int			*buff_no;
	int			*buff_we;
	int			*buff_ea;
	int			*buff_so;
	int			wall_height;
	char		*txt_so;
	char		*txt_no;
	char		*txt_we;
	char		*txt_ea;
	t_player	*player;
	t_ray		*ray;
	t_colors	*colors;
	t_mini_map	*mini_m;
	t_img		mini_map;
}	t_map;

typedef struct s_var
{
	int		ptw_y;
	int		ptw_x;
	int		ptw_iy;
	int		ptw_ix;
	int		*ptw_buffer;
	double	xstep;
	double	ystep;
	double	xintercept;
	double	yintercept;
	double	next_x;
	double	next_y;
	double	next_xv;
	double	next_yv;
	double	hor_hitdis;
	double	ver_hitdis;
	double	new_hitx;
	double	new_hity;
}	t_var;

//initialize
void			initialize(t_map *mapp);
void			initialize_player(t_map *mapp);
void			initialize_xpm(t_map *mapp);
void			initialize_colors(char **map, char *s, int i, t_map *test);

//player functions
void			move_player(t_map *mapp);

//map functions
char			**map_read(int fd);
int				draw_map(t_map *mapp);
void			game_start(char **grid, t_map *mapp);

//backup functions
size_t			ft_strlen(const char *str);
char			*ft_strchr(const char *str, int pos);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strdup(const char *src);
char			**ft_split(char const *s, char c);
double			normlize_angle(double r_angle);
double			distancepythagoras(double px, double py,
					double hitx, double hity);
void			set_hor_distance(t_ray *ray, t_var *var);
void			set_vert_distance(t_ray *ray, t_var *var);
size_t			ft_strlen(const	char *s);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strjoin(char const *s1, char const *s2);
char			**ft_split(char const *s, char c);
void			ft_allocation_err(void);
int				print_error(char *str, int ret);
char			**ft_free_str_map(char *s, char **map);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strdup(const char *s1);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
int				ft_isdigit(int c);
int				ft_atoi(const char *str);
int				ft_isdigit(int c);

//key hooks
int				key_up(int key, t_map *mapp);
int				key_down(int key, t_map *mapp);
int				close_window(int key, void *param);

//rays
void			initialize_rays(t_map *mapp);
void			castallrays(t_map *mapp);
void			casting(t_map *mapp, t_player *player, t_ray *ray);
int				is_wall(t_map *m, int x, int y, char identf);
int				is_end_window(t_map *m, double x, double y);

//3d walls
void			projectewall3d(t_map *m);

//ceilling and floor
void			ceilling_floor_render(t_map *mapp, int state, int color);
unsigned long	create_rgb(int r, int g, int b);

//textures
void			get_texture_buff(t_map *info);
void			get_no_texture(t_map *info);
void			get_we_texture(t_map *info);
void			get_so_texture(t_map *info);
unsigned int	get_color(t_img img, int x, int y);
void			initialize_strct(char **map, char player, t_map *test);
void			set_screen_pixel(t_img *screen, int i, int j, int color);
void			draw_square(int x, int y, char c, t_img *img);

//parsing
int				check_extension(char *str);
char			**get_map(int fd);
int				check_map_ressources(char **map, t_map *test);
int				check_six_lines(char *s);
int				check_duplicate_direction(char **sixlines);
int				check_xpm_files(char **sixlines);
int				check_colors(char **sixlines, int i, int k, int j);
int				check_player_map_elems(char **map, int i, char *p);
int				check_player(char **map, int i);
int				check_map_surround(char **map, int i, char c, char p);
char			**true_map(t_map *test, char **map);
int				check_six_lines(char *s);
int				check_duplicate_direction(char **sixlines);
char			*read_xpm(int fd);
int				full_xpm(char *s);
int				check_xpm_files(char **sixlines);
int				check_map_surround(char **map, int i, char c, char p);
int				check_map_utils(char **map, int i, int j, char p);

#endif
