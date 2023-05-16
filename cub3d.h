/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-maza <rel-maza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 20:55:42 by mzridi            #+#    #+#             */
/*   Updated: 2023/05/16 23:04:57 by rel-maza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# define FOV 1.0472
# define WINDOW_HEIGHT 720
# define WINDOW_WIDTH 1280
# define MAP_WIDTH 26
# define MAP_HEIGHT 5
# define MINIMAP_HEIGHT 100
# define MINIMAP_WIDTH 200
# define MOVE_SPEED 5
# define ROTATION_SPEED 0.1
# define BLOCK_SIZE 32

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_point {
	double	x;
	double	y;
}	t_point;

typedef struct s_ray {
	double	x;
	double	y;
	double	angle;
	double	dx;
	double	dy;
	char	type;
	t_point	wall;
}				t_ray;

typedef struct s_player {
	double	x;
	double	y;
	double	dx;
	double	dy;
	double	angle;
	int		v_move_direction;
	int		h_move_direction;
	int		rotation_direction;
	int		last_mouse_x;
	int		mouse_x;
}				t_player;

typedef struct s_texture {
	void	*img;
	int		*data;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
}				t_texture;

typedef struct s_textures {
	t_texture	north;
	t_texture	south;
	t_texture	east;
	t_texture	west;
}				t_textures;

typedef struct s_line
{
	char			*line;
	struct s_line	*next;
}		t_line;

typedef struct cub3D_s
{
	int		width;
	int		height;
	int		max_lenght;
	char	**map_arr;
	t_line	*head;
	int		first_line;
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	char	*floor_color;
	char	*ceiling_color;
	char	*floor_color_r;
	char	*floor_color_g;
	char	*floor_color_b;
	char	*ceiling_color_r;
	char	*ceiling_color_g;
	char	*ceiling_color_b;
	int		*floor_color_int;
	int		*ceiling_color_int;
	int		map_width;
	int		map_height;
	int		fd;
}	t_cub3D;

typedef struct s_var {
	t_data		img;
	t_player	player;
	char		**map;
	void		*mlx;
	void		*mlx_win;
	t_textures	textures;
	int			map_height;
	int			*map_widths;
	int			map_width;
	t_cub3D		*cub;
}	t_var;

void		init_player(t_player *player, int i, int j, char dir);
t_var		*init_data(t_cub3D *cub);
int			check_wall(t_var *data, int i, int is_horizontal);
int			key_press(int keycode, t_var *data);
int			to_minmap(t_var *data, int x, int y);
void		put_miniplayer(t_var *data, t_player *player);
void		draw_minimap(t_var *data);
void		put_block_mini(t_var *data, int x, int y, int color);
void		draw_rays(t_var *data);
void		draw_ray(t_var *data, t_ray *ray);
int			render_next_frame(t_var *data);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
t_point		first_h_inter(t_var *data, t_ray *ray);
t_point		ith_h_inter(t_var *data, t_ray *ray, int i);
t_point		ith_v_inter(t_var *data, t_ray *ray, int i);
t_point		dist_to_h_wall(t_var *data, t_ray *ray);
t_point		dist_to_v_wall(t_var *data, t_ray *ray);
double		distance_wall(t_var *data, t_ray *ray);
void		draw_3d(t_var *data);
int			is_facing_up(float angle);
int			is_facing_left(float angle);
void		put_point(t_data *data, int x, int y, int color);
char		get_map_value(t_var *data, t_point point);
int			key_release(int keycode, t_var *data);
int			mouse_move(int x, int y, t_var *data);
int			get_wall_color(t_var *data, t_ray ray, int y, int wall_height);
t_point		get_texture_column(t_var *data, t_ray ray, int y, int wall_height);
t_texture	get_texture(t_var *data, t_ray ray);
double		normalize_angle(double angle);
//parcing functions
char		*get_next_line(int fd);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strtrim(char **s1, char *set);
int			ft_strlen(char *s);
char		*get_line(int fd);
int			ft_checkline(char *line);
void		fill_map_back(t_cub3D *cub, t_line *head);
int			ft_lstsize(t_line *lst);
int			ft_lsttoarray(t_line *map, t_cub3D *cub);
char		*rightpad(char *str, int n);
void		leftpad(char *str);
void		fill_map(t_cub3D *cub, t_line *head);
int			ft_checkforspaces(t_cub3D *cub);
int			ft_checkwall(t_cub3D *cub);
int			ft_checkifclosed(t_cub3D *cub, t_line *head);
int			is_valid_map( char *filename);
size_t		ft_strlcpy(char *dst, char *src, size_t dstsize);
char		*ft_strcpy(char *dest, const char *src);
char		*ft_strdup(char *src);
int			ft_atoi(const char *s1);
int			ft_isdigit(int c);
char		*ft_strcat(char *dest, char *src);
char		*ft_substr(char *s, unsigned int start, size_t len);
char		**ft_split(char const *s, char c);
int			map_height(char **map);
int			init_textures(t_var *data);
t_point		add_point_to_player(t_var *data, t_point point, t_ray *ray);
char		get_map_value(t_var *data, t_point point);
t_point		first_h_inter(t_var *data, t_ray *ray);
t_point		ith_h_inter(t_var *data, t_ray *ray, int i);
t_point		first_v_inter(t_var *data, t_ray *ray);
int			ft_lstsize(t_line *lst);
int			ft_lsttoarray(t_line *map, t_cub3D *cub);
char		*rightpad(char *str, int n);
void		leftpad(char *str);
void		fill_map(t_cub3D *cub, t_line *head);
int			is_valid_map( char *filename);
int			filling(t_cub3D *cub, t_line *tmp);
t_line		*read_map(t_cub3D *cub);
void		hooks(t_var *data);
void		check_forma(t_cub3D *cub, t_line *tmp);
void		check_file(char *filename, t_cub3D *cub);
int			ft_colorparce(t_cub3D *cub);
int			ft_checkcolor(char *str);
int			convert_ceiling_color(t_cub3D *cub);
int			convert_floor_color(t_cub3D *cub);
int			ft_checkforplayer(t_cub3D	*cub);
int			ft_check_position(t_cub3D *cub);
int			ft_checkplayercolumn(int i, int j, t_cub3D *cub);
int			ft_checkplayerrow(int i, int j, t_cub3D *cub);
int			ft_findplayer(char c);
int			ft_checkformultiplemap(t_cub3D *cub);
int			ft_checkifclosed(t_cub3D *cub, t_line *head);
int			check_utils(t_cub3D *cub, int i, int j);
int			init_width_height(t_cub3D *cub);
int			ft_sortpathtexture(t_cub3D *cub);
int			check_direction(int i, int j, t_cub3D *cub);
void		ft_sortcolorpath(int i, int j, t_cub3D *cub);
void		ft_sortwallpath(int i, int j, t_cub3D *cub);
int			ft_countpathtexture(t_cub3D *cub);
int			check_ea(int i, int j, t_cub3D *cub);
int			check_we(int i, int j, t_cub3D *cub);
int			check_so(int i, int j, t_cub3D *cub);
int			check_no(int i, int j, t_cub3D *cub);
int			ft_checkwall(t_cub3D *cub);
int			ft_checkforspaces(t_cub3D *cub);
#endif